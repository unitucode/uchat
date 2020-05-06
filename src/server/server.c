#include "server.h"
#include "sqlite3.h"

static void *doit(void *arg);

static int callback(void* data, int argc, char** argv, char** azColName) { 
    int i; 
    fprintf(stderr, "%s: ", (const char*)data); 
  
    for (i = 0; i < argc; i++) { 
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); 
    } 
    printf("\n"); 
    return 0; 
} 

int main(int argc, char **argv) {
    sqlite3* DB;
    int vlad = 0; 
    vlad = sqlite3_open( "vlad.db", &DB);
    // char *sql = "CREATE TABLE PERSON("
    //             "ID INT PRIMARY KEY     NOT NULL, "
    //             "NAME           TEXT    NOT NULL, "
    //             "SURNAME          TEXT     NOT NULL, "
    //             "AGE            INT     NOT NULL, "
    //             "ADDRESS        CHAR(50), "
    //             "SALARY         REAL );";
    char *query = "SELECT * FROM PERSON;";
    printf("до вставленяня\n\n");
    sqlite3_exec(DB, query, callback, NULL, NULL);
//    sql = ("INSERT INTO PERSON VALUES(1, 'STEVE', 'GATES', 30, 'PALO ALTO', 1000.0);"
//                "INSERT INTO PERSON VALUES(2, 'BILL', 'ALLEN', 20, 'SEATTLE', 300.22);"
//                "INSERT INTO PERSON VALUES(3, 'PAUL', 'JOBS', 24, 'SEATTLE', 9900.0);"); 
    printf("after вставленяня\n\n");
    char *sql = "INSERT INTO PERSON VALUES(2, 'BILL', 'ALLEN', 20, 'SEATTLE', 300.22);";
    // vlad = sqlite3_exec(DB, sql, callback, 0, 0); 
    // if (vlad != SQLITE_OK) {
    //     printf("\nerror!!!\n\n");
    // }
    // else {
    //     printf("\ncreated Successfully\n\n");
    // }
    // sql = "DELETE FROM PERSON WHERE ID = 2;"; 
    vlad = sqlite3_exec(DB, sql, callback, 0, 0); 
    if (vlad != SQLITE_OK) {
        printf("\nerror!\n\n");
    }
    else {
        printf("\n ok\n\n");
    }
    sqlite3_close(DB);
    int listen_fd, *iptr;
    pthread_t tid;
    socklen_t addrlen, len;
    struct sockaddr *cliaddr;
    
    if (argc == 2) {
        listen_fd = mx_tcp_listen(argv[1], &addrlen);
    }
    else {
        printf("usage\n");
        exit(1);
    }
    cliaddr = mx_malloc(addrlen);

    while (1) {
        len = addrlen;
        iptr = mx_malloc(sizeof(int));
        *iptr = mx_accept(listen_fd, cliaddr, &len);
        mx_pthread_create(&tid, NULL, &doit, iptr);
    }
}

void str_echo(int sockfd) {
    ssize_t n;
    char buf[1024];

again:
    while ((n = read(sockfd, buf, 1024)) > 0)
        write(sockfd, buf, n);
    
    if (n < 0 && errno == EINTR)
        goto again;
    else if (n < 0)
        exit(1);

}

static void *doit(void *arg) {
    int connfd = *((int *)arg);
    printf("connfd = %d\n", connfd);
    free(arg);
    pthread_detach(pthread_self());
    str_echo(connfd);
    mx_close(connfd);
    return NULL;
}
