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

static void test();

int main(int argc, char **argv) {
    test();
    t_chat *chat = mx_init_chat(argc, argv);
    t_client *client = NULL;
    t_ssl_con *ssl = NULL;
    
    mx_change_working_dir();
    chat->database = mx_open_db(MX_DB);
    client = NULL;
    ssl = mx_init_ssl(SERVER);
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

static void test() {
    sqlite3 *db = mx_open_db(MX_DB);
    
    // t_db_room *room = malloc(sizeof(t_db_room));
    // room->customer_id = 1;
    // room->desc = NULL;
    // room->room_name = "name";
    // room->type = GLOBAL_CHAT;
    // for (int i = 0; i < 100; i++)
    //     mx_insert_room_into_db(db, room);
    // mx_free_room(&room);
    
    // t_db_user *user = malloc(sizeof(t_db_user));
    // user->desc = "desc";
    // user->login = "login5";
    // user->name = "name5";
    // user->pass = "pass";
    // user->token = "token";
    // mx_insert_user_into_db(db, user);

    // for (int i = 2; i < 20; i++)
        // mx_insert_member_into_db(db, 1, 1, SIMPLE);

    // t_db_message *message = malloc(sizeof(t_db_message));
    // message->user_id = 1;
    // message->room_id = 1;
    // message->message = "hello";
    // message->name_file = NULL;
    // message->size = 0;
    // message->type = TEXT_MSG;
    // for (int i = 0; i < 1000; i++) {
    //     mx_insert_message(db, message);
    // }

    // mx_get_user_by_login(db, "login1");

    // cJSON *json_1 = cJSON_CreateObject();
    // cJSON_AddStringToObject(json_1, "name", "my first and last name");
    // cJSON_AddStringToObject(json_1, "pass", "password");
    // cJSON_AddStringToObject(json_1, "login", "login13");
    // cJSON_AddStringToObject(json_1, "token", "token144");
    // cJSON_AddStringToObject(json_1, "desc", "desc553");
    // t_db_user *user = mx_parse_json_user(json_1);
    // if (user) {
    //     printf("name \t->)-<>-(-> %s\n", user->name);
    //     printf("login\t->)-<>-(-> %s\n", user->login);
    //     printf("desc \t->)-<>-(-> %s\n", user->desc);
    //     printf("pass \t->)-<>-(-> %s\n", user->pass);
    //     printf("token\t->)-<>-(-> %s\n", user->token);
    //     mx_insert_user_into_db(db, user);
    // }

    // cJSON *message_j = cJSON_CreateObject();
    // cJSON_AddNumberToObject(message_j, "room_id", 1);
    // cJSON_AddNumberToObject(message_j, "user_id", 1);
    // cJSON_AddNumberToObject(message_j, "type", DB_FILE_MSG);
    // cJSON_AddNumberToObject(message_j, "file_size", 0);
    // cJSON_AddStringToObject(message_j, "message", "");
    // cJSON_AddStringToObject(message_j, "file_name", "name_file");
    // t_db_message *message = mx_parse_message(message_j);
    // if (message) {
    //     printf("parse Ok !\n");
    //     printf("file_size\t->)-<>-(-> %s\n", message->file_name);
    //     printf("file_size\t->)-<>-(-> %llu\n", message->file_size);
    //     printf("message  \t->)-<>-(-> %s\n", message->message);
    //     printf("room_id  \t->)-<>-(-> %llu\n", message->room_id);
    //     printf("user_id  \t->)-<>-(-> %llu\n", message->user_id);
    //     printf("type     \t->)-<>-(-> %d\n", message->type);
    //     mx_insert_message(db, message);
    // }

    // cJSON *room_j = cJSON_CreateObject();
    // cJSON_AddStringToObject(room_j, "name", "room_name");
    // cJSON_AddStringToObject(room_j, "desc", "");
    // cJSON_AddNumberToObject(room_j, "customer_id", 1);
    // cJSON_AddNumberToObject(room_j, "type", DB_PRIVAT_CHAT);
    // t_db_room *room = mx_parse_json_room(room_j);
    // if (room) {
    //     printf("create !\n");
    //     printf("name        \t->)-<>-(-> %s\n", room->room_name);
    //     printf("desc        \t->)-<>-(-> %s\n", room->desc);
    //     printf("customer_id \t->)-<>-(-> %llu\n", room->customer_id);
    //     printf("pass        \t->)-<>-(-> %d\n", room->type);
    //     mx_insert_room_into_db(db, room);
    // }

    // cJSON *json0 = mx_search_room(db, "n");
    // gchar *string0 = cJSON_Print(json0);
    // printf("%s\n", string0);

    // printf("%llu\n", mx_get_time(DB_SECOND));
    // printf("%llu\n", mx_get_time(DB_MILISECOND));
    // printf("%llu\n", mx_get_time(DB_MICROSECOND));

    // cJSON *json = mx_get_rooms(db, 0, 1);
    // gchar *string = cJSON_Print(json); 
    // printf("%s\n", string);

    // cJSON *json1 = mx_get_users(db, 0);
    // gchar *string1 = cJSON_Print(json1);
    // printf("%s\n", string1);

    mx_close_db(db);
    printf("Ok\n");
    system("leaks -q uchat_server");
    exit(1);
}

