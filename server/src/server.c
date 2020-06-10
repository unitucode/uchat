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
    // sqlite3 *database = mx_server_data_open(MX_DB);
    // t_db_user *user = mx_insert_user_into_db(database, "login1", "password", "token");
    // printf("%s\n", user->login);
    // printf("%s\n", user->token);
    // printf("%s\n", user->password);
    // sqlite3 *database =  mx_server_data_open(MX_DB_USER);
    // // char *string = cJSON_Print(mx_create_json_object(database, "vlad"));
    // char *string = cJSON_Print(mx_get_last_message(database, "chat_of_vlad", 50));
    // printf("%s\n", string);
    // // mx_json();
    // // t_dl_list *list = mx_parse_json(string);
    // // t_room *room = (t_room*)list->front->data;
    // // printf("room_customer -> %s\n", room->customer);
    // mx_close_database(database);
    // printf("Ok\n");
    // exit(1);
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
