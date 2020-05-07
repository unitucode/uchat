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
    
    while (1) {
        client = mx_new_client(chat->len);
        client->socket_fd = mx_accept(chat->listen_fd, client->cliaddr, &client->len);
        mx_get_client_info(client);
        mx_push_node(chat->clients, client, MX_LIST_BACK);
        chat->current_client = client;
        mx_pthread_create(&client->tid, NULL, &client_handler, chat);
    }
}
