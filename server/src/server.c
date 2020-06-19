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
    // room->customer = "customer";
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

    mx_get_user_by_login(db, "login1");

    // cJSON *json = mx_get_rooms(db, 0, 1);
    // gchar *string = cJSON_Print(json); 
    // printf("%s\n", string);

    // cJSON *json1 = mx_get_users(db, 0);
    // gchar *string1 = cJSON_Print(json1);
    // printf("%s\n", string1);

    mx_close_database(db);
    printf("Ok\n");
    system("leaks -q uchat_server");
    exit(1);
}

