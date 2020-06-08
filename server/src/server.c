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
    // sqlite3 *database = mx_server_data_open(MX_DB);
    // printf("%s\n", mx_create_request_message(database, "name_room", 1));
    // cJSON *message = mx_get_new_messages(database, "name  2", 1591633200, 1);
    // char *string = cJSON_Print(message);
    // printf("%s\n", string);
    // mx_delete_message(database, "name  2", 1);
    // t_db_message *message = mx_insert_message_into_db(database, "hello guys", "vlad", "name  2");
    // mx_free_message(&message);
    // for (int i = 0; i < 2; i++) {
    //     printf("%s\n%s\n", room->name_room, room->customer);
    // }
    // printf("vlad\n");
    // mx_insert_message_into_db(database, "hello", "login", "name1");
    // t_db_room *room = mx_insert_room_into_db(database, "name  2", "gorila");
    // printf("%s\n", message->name_room);
    // printf("%s\n", message->message);
    // printf("%s\n", message->login);
    // printf("%d\n", message->id_message);
    // printf("%ld\n", message->date);
    // mx_free_room(&room);
    // mx_delete_room(database, "name2");
    // char *error = malloc(100);
    // printf("%d\n", sqlite3_exec(database, "DELETE FROM ROOMS WHERE NAME_ROOM = 'name2'; DROP TABLE 'name2'", 0, 0, &error));
    // printf("%s\n", error);
    // cJSON *rooms = mx_get_rooms(database, 0);
    // char *string = cJSON_Print(rooms);
    // system("leaks -q uchat_server");
    // printf("%s\n", string);
    // mx_json();
    // t_dl_list *list = mx_parse_json(string);
    // t_room *room = (t_room*)list->front->data;
    // printf("room_customer -> %s\n", room->customer);
    mx_close_database(database);
    system("leaks -q uchat_server");
    printf("Ok\n");
    exit(1);
    t_chat *chat = mx_init_chat(argc, argv);
    t_client *client = NULL;
    t_ssl_con *ssl = NULL;

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
