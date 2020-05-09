#include "client.h"
#include <sqlite3.h>
#include <stdlib.h>

static int sockfd;
static FILE *fp;
static int done;

void *copyto(void *arg) {
    char sendline[1024];
    arg = NULL;
    while (fgets(sendline, 1024, fp) != NULL)
        write(sockfd, sendline, strlen(sendline));
    
    shutdown(sockfd, SHUT_WR);
    done = 1;
    return NULL;
}

void str_cli(FILE *fp_arg, int sockfd_arg) {
    char *recvline = mx_malloc(1025);
    pthread_t tid;

    sockfd = sockfd_arg;
    fp = fp_arg;
    mx_pthread_create(&tid, NULL, copyto, NULL);

    FILE *fd = fdopen(sockfd, "r");
    size_t len = 0;
    while (getline(&recvline, &len, fd) > 0)
        fputs(recvline, stdout);

    if (done == 0)
        exit(1);
}

int callback(void* data, int argc, char** argv, char** azColName) {  
    fprintf(stderr, "%s: ", (const char*)data); 
  
    for (int i = 0; i < argc; i++) { 
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); 
    }
    // printf("\n"); 
    printf("Ok\n");
    return 0; 
} 

int callbackvlad(void *message, int argc, char** argv, char **data_parametr) {

    for (int i = 0; i < argc; i++) {
        printf("%s -> %s\n", data_parametr[i], argv[i]);
        if (strcmp("MESSAGE", data_parametr[i]) == 0 && argv[i] != NULL) {
            message = strdup(argv[i]);
        }
    }
    printf("Ok\n");
    return 0;
}

int main(int argc, char **argv) {
    int sockfd;
    sqlite3* DB;
    int vlad = 0;
    // char *message = NULL;
    sqlite3_stmt *stmt; 
    vlad = sqlite3_open( "vlad.db", &DB);
    char *sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY,MESSAGE)"  \
         "VALUES (67, 'ura', 17, 'boratin', 20043.00, 'oh my zsh'); ";
    vlad = sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);
    if ((vlad = sqlite3_step(stmt)) == SQLITE_BUSY) {
        printf("ERROR !!!!");
    } 
    sqlite3_finalize(stmt);
    // while ((vlad = sqlite3_step(stmt)) == SQLITE_ROW) {
        // message = (char *)sqlite3_column_text(stmt, 1);
        // printf("%s\n", message);
    // }
    // sqlite3_str *new = sqlite3_str_new(DB);
    // sqlite3_str_appendall(new, "I am the finished");
    // char *str_new = sqlite3_str_finish(new);
    // printf("\n%s\n", str_new);
    // char *sql1 = "UPDATE COMPANY set MESSAGE = 'I AM PROGRAMING' WHERE ID = 6";
    // vlad = sqlite3_exec(DB, sql, callback, 0, 0); 
    sql = "SELECT * from COMPANY";
    
    vlad = sqlite3_exec(DB, sql, callbackvlad, 0, 0);
    // sqlite3_finalize(stmt);
    sqlite3_close(DB);
    system("leaks -q uchat");
    if (argc != 3) {
        printf("usage\n");
        exit(1);
    }
    sockfd = mx_tcp_connect(argv[1], argv[2]);
    str_cli(stdin, sockfd);
}

