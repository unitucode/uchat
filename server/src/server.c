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
    
    // get message by id
    // cJSON *vlad = mx_get_old_messages();
    // cJSON *vlad = mx_get_new_messages_by_id(database, 1, 0, 50);
    // cJSON *vlad = mx_get_curr_messages_by_id(database, 23, 50);
    // printf("%s\n", cJSON_Print(vlad));

    // create room                  Ok
    t_db_room *room = mx_insert_room_into_db(database, "name7", "customer");
    if (!room)
        exit(0);
    printf("%s\n", room->name_room);
    printf("%s\n", room->customer);
    printf("%ld\n", room->date);
    printf("%d\n", room->id);
    printf("%s\n", room->description);
    mx_free_room(&room);

    // test valid database
    // char *request = "";
    // sqlite3_preparev_2(database);

    // sqlite3_step(stmt);

    // edit room name                Ok
    // mx_edit_name_room(database, 5, "edit.002");

    // // create message               Ok
    // for (int i = 0; i < 100; i++) {
    //     t_db_message *message = mx_insert_message_into_db_by_id(database, "ffd", "login", 1);
    //     mx_free_message(&message);  
    // }

    // delete room by id            Ok
    // mx_delete_room_by_id(database, 9);

    // if exists room               Ok
    // printf("->\t%d\n", (int)mx_is_exists_room_by_id(database, 27));

    // delete message               Ok
    // for (int i = 0; i < 1000; i++) {
    //     mx_delete_message(database, 23, i);
    // }

    // edit login                    Ok
    // mx_edit_name_user(database, "login5", "login1");

    // delete user                    Ok
    // mx_delete_user(database, "login1");


    // get count                Ok 
    // printf("count rooms ->\t %llu\n", mx_get_count_rooms(database));
    // printf("count users ->\t %llu\n", mx_get_count_users(database));
    // printf("count mssgs ->\t %llu\n", mx_get_count_messages(database, 1));

    // count 
    // sqlite3_stmt *stmt;
    // int rv = SQLITE_OK;
    
    // rv = sqlite3_prepare_v2(database, "select count() from users", -1, &stmt, NULL);
    // printf("rv prepare -> %d\n", rv);
    // rv = sqlite3_step(stmt);
    // printf("rv step    -> %d\n", rv);
    // printf("count      -> %d\n", sqlite3_column_int(stmt, 0));
    // sqlite3_finalize(stmt);

    // create user                  Ok 
    // t_db_user *user = mx_insert_user_into_db(database, "login", "password", "token");
    // if (user) {
    //     printf("login -> %s\n", user->login);
    //     printf("desc -> %s\n", user->description);
    //     printf("pass -> %s\n", user->password);
    //     printf("token -> %s\n", user->token);
    //     printf("date -> %ld\n\n\n", user->date);
    //     mx_free_user(&user);
    // }
    // get user 
    // t_db_user *user = mx_get_user_by_login(database, "login8");
    // if (user) {
    //     printf("login -> %s\n", user->login);
    //     printf("desc -> %s\n", user->description);
    //     printf("pass -> %s\n", user->password);
    //     printf("token -> %s\n", user->token);
    //     printf("date -> %ld\n", user->date);
    //     mx_free_user(&user);
    // }

    mx_close_database(database);
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
