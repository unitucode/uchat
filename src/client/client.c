#include "client.h"
#include <sqlite3.h>

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

static int callback(void* data, int argc, char** argv, char** azColName) {  
    fprintf(stderr, "%s: ", (const char*)data); 
  
    for (int i = 0; i < argc; i++) { 
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); 
    } 
    printf("\n"); 
    return 0; 
} 

int main(int argc, char **argv) {
    int sockfd;
    sqlite3* DB;
    int vlad = 0; 
    vlad = sqlite3_open( "vlad.db", &DB);

    char *sql1 = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "\
                 "VALUES (5, 'vlad', 45, 'starichervicha', 200000000.00 ); ";
    vlad = sqlite3_exec(DB, sql1, callback, 0, 0); 
    char *sql = "SELECT ID from COMPANY WHERE NAME = 'vlad'";

    vlad = sqlite3_exec(DB, sql, callback, (void*)"company worker", 0); 
    sqlite3_close(DB);
    if (argc != 3) {
        printf("usage\n");
        exit(1);
    }
    sockfd = mx_tcp_connect(argv[1], argv[2]);
    str_cli(stdin, sockfd);
}

