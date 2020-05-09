#include "server.h"
#include "sqlite3.h"

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
    t_chat *chat = mx_init_chat(argc, argv);
    t_client *client = NULL;
<<<<<<< HEAD
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
    char **base = {"vlad", "sasha", "pasha", "ura"}
    char *sql = "INSERT INTO PERSON VALUES(2, 'BILL', 'ALLEN', 20, 'SEATTLE', 300.22);";
    for () {

    }
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
    
=======
    t_ssl_con *ssl = mx_init_ssl(SERVER);

    mx_logger(MX_LOG_FILE, LOGMSG,
              "started server pid[%d]: %s %s\n", getpid(), argv[0], argv[1]);
>>>>>>> 996a8bce0f87019e79777fe2e3979b07b9dad6d9
    while (1) {
        client = mx_new_client(chat->len);
        client->socket_fd = mx_accept(chat->listen_fd,
                                      client->cliaddr, &client->len);
        ssl->ssl = SSL_new(ssl->ctx);
        SSL_set_fd(ssl->ssl, client->socket_fd);
        if (SSL_accept(ssl->ssl) == -1)
            mx_elogger(MX_LOG_FILE, LOGERR, "ssl_accept\n");
        client->chat = chat;
        client->ssl = ssl->ssl;
        mx_connect_client(client);
    }
}
