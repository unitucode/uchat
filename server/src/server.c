#include "server.h"
#include "sqlite3.h"

void mx_change_working_dir(void) {
    #ifdef MX_SERVER
    if (chdir(MX_SERVER)) {
        mx_elogger(NULL, LOGERR,
                   "No working directory %s\n", MX_SERVER);
    }
    #else
    mx_elogger(NULL, LOGERR, "No working directory");
    #endif
}

int main(int argc, char **argv) {
    // mx_change_working_dir();
    sqlite3 *database = mx_server_data_open(MX_DB);
    
    // create room
    t_db_room *room = mx_insert_room_into_db(database, "name_room", "customer");
    mx_free_room(&room);

    // create message
    for (int i = 0; i < 100; i++) {
        t_db_message *message = mx_insert_message_into_db(database, "hello", "login", "name_room");
        mx_free_message(&message);
    }
    
    // delete message
    // for (int i = 0; i < 20; i++) {
    //     mx_delete_message(database, "name_room", i);
    // }

    // t_db_user *user = mx_insert_user_into_db(database, "login", "password", "token");
    // printf("login -> %s\n", user->login);
    // printf("pass -> %s\n", user->password);
    // printf("token -> %s\n", user->token);
    // printf("date -> %ld\n", user->date);
    // mx_close_database(database);
    system("leaks -q uchat_server");
    printf("Ok\n");
    exit(1);
    t_chat *chat = mx_init_chat(argc, argv);
    t_client *client = NULL;
    t_ssl_con *ssl = NULL;
    
    mx_change_working_dir();
    chat->database = mx_server_data_open(MX_DB);
    client = NULL;
    ssl = mx_init_ssl(SERVER);
    mx_create_table_users(chat->database);
    mx_logger(MX_LOG_FILE, LOGMSG,"started server pid[%d]: %s %s\n", getpid(), argv[0], argv[1]);
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
    mx_deinit_chat(&chat);
}
