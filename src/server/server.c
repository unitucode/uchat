#include "server.h"
#include <sqlite3.h>

static int callback(void* data, int argc, char** argv, char** azColName) {  
    fprintf(stderr, "%s: ", (const char*)data); 
  
    for (int i = 0; i < argc; i++) { 
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); 
    } 
    printf("\n"); 
    return 0; 
} 

int main(int argc, char **argv) {
    // start vlad
    sqlite3* DB;
    int vlad = 0; 
    vlad = sqlite3_open( "vlad.db", &DB);
    printf("vlad = %d\n", vlad);
    char *sql = "CREATE TABLE COMPANY("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "AGE            INT     NOT NULL," \
      "ADDRESS        CHAR(50)," \
      "SALARY         REAL );";
    vlad = sqlite3_exec(DB, sql, 0, 0, 0); 
    printf("vlad = %d\n", vlad);
    sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";
    vlad = sqlite3_exec(DB, sql, callback, 0, 0); 
    sql = "SELECT * from COMPANY";
    vlad = sqlite3_exec(DB, sql, callback, (void*)"company worker", 0); 
    if (vlad != SQLITE_OK) {
        printf("\nerror!\n\n");
        printf("%d\n", vlad);
    }
    else {
        printf("\n ok\n\n");
    }
    sqlite3_close(DB);
    //end vlad
    t_chat *chat = mx_init_chat(argc, argv);
    t_client *client = NULL;
    while (1) {
        client = mx_new_client(chat->len);
        client->socket_fd = mx_accept(chat->listen_fd, client->cliaddr, &client->len);
        mx_get_client_info(client);
        mx_push_node(chat->clients, client, MX_LIST_BACK);
        chat->current_client = client;
        mx_pthread_create(&client->tid, NULL, &client_handler, chat);
    }
}
