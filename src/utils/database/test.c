#include "utils.h"

void mx_test_users() {
    printf("start test users !\n\n");
    sqlite3 *database = mx_server_data_open(MX_DB_USER);
    mx_create_table(MX_USERS_TABLE, database);
    mx_insert_user("vlad", "uchat", "token",database);
    mx_insert_user("sasha", "kill", "token", database);
    mx_insert_user("ura", "dolli", "token", database);
    mx_insert_user("pasha", "Robert", "token", database);
    t_user *user = mx_get_user_by_login("vlad", database);
    if (user == NULL) {
        printf("error user\n");
        exit(1);
    }
    printf("LOGIN -> \t%s\n", user->login);
    printf("PASS -> \t%s\n", user->password);
    printf("TOKEN -> \t%s\n", user->token);
    printf("PERMISSION -> \t%d\n\n", user->permission);

    user = mx_get_user_by_login("sasha", database);
    if (user == NULL) {
        printf("error user\n");
        exit(1);
    }
    printf("LOGIN -> \t%s\n", user->login);
    printf("PASS -> \t%s\n", user->password);
    printf("TOKEN -> \t%s\n", user->token);
    printf("PERMISSION -> \t%d\n\n", user->permission);

    user = mx_get_user_by_login("ura", database);
    if (user == NULL) {
        printf("error user\n");
        exit(1);
    }
    printf("LOGIN -> \t%s\n", user->login);
    printf("PASS -> \t%s\n", user->password);
    printf("TOKEN -> \t%s\n", user->token);
    printf("PERMISSION -> \t%d\n\n", user->permission);
    
    user = mx_get_user_by_login("pasha", database);
    if (user == NULL) {
        printf("error user \n");
        exit(1);
    }
    printf("LOGIN -> \t%s\n", user->login);
    printf("PASS -> \t%s\n", user->password);
    printf("TOKEN -> \t%s\n", user->token);
    printf("PERMISSION -> \t%d\n\n", user->permission);
    mx_close_database(database);
    printf("end test users !\n\n");
}

void mx_test_message() {
    printf("start test message !\n\n");
    sqlite3 *database = mx_server_data_open(MX_DB_USER);
    mx_create_table(MX_MESSAGE_TABLE, database);
    mx_insert_message("vlad", 12, "json", database);
    mx_insert_message("sasha", 13, "json", database);
    mx_insert_message("ura", 14, "json", database);
    mx_insert_message("pasha", 15, "json", database);
    t_message *message = mx_get_message_by_login("vlad", database);
    if (message == NULL) {
        printf("error message\n");
        exit(1);
    }
    printf("ID_MESSAGE -> \t%d\n", message->id_message);
    printf("LOGIN -> \t%s\n", message->login);
    printf("JSON -> \t%s\n", message->json);
    printf("DATE -> \t%lld\n\n", message->date);
    message = mx_get_message_by_login("sasha", database);
    if (message == NULL) {
        printf("error message\n");
        exit(1);
    }
    printf("ID_MESSAGE -> \t%d\n", message->id_message);
    printf("LOGIN -> \t%s\n", message->login);
    printf("JSON -> \t%s\n", message->json);
    printf("DATE -> \t%lld\n\n", message->date);
    message = mx_get_message_by_login("ura", database);
    if (message == NULL) {
        printf("error message\n");
        exit(1);
    }
    printf("ID_MESSAGE -> \t%d\n", message->id_message);
    printf("LOGIN -> \t%s\n", message->login);
    printf("JSON -> \t%s\n", message->json);
    printf("DATE -> \t%lld\n\n", message->date);
    message = mx_get_message_by_login("pasha", database);
    if (message == NULL) {
        printf("error message\n");
        exit(1);
    }
    printf("ID_MESSAGE -> \t%d\n", message->id_message);
    printf("LOGIN -> \t%s\n", message->login);
    printf("JSON -> \t%s\n", message->json);
    printf("DATE -> \t%lld\n\n", message->date);
    mx_close_database(database);
    printf("end test message !\n\n");
}

void mx_test_member() {
    printf("start test member !\n\n");
    sqlite3 *database = mx_server_data_open(MX_DB_USER);
    mx_create_table(MX_MEMBER_TABLE, database);    
    mx_insert_memeber(1, "vlad", database);
    mx_insert_memeber(2, "sasha", database);
    mx_insert_memeber(3, "pasha", database);
    mx_insert_memeber(4, "ura", database);
    printf("end test member !\n\n");
}

void mx_test_room() {
    printf("start test room !\n\n");
    sqlite3 *database = mx_server_data_open(MX_DB_USER);
    mx_create_table(MX_ROOMS_TABLE, database);
    mx_insert_room("vlad", "uchat", database);
    mx_insert_room("sasha", "kill", database);
    mx_insert_room("ura", "dolli", database);
    mx_insert_room("pasha", "Robert", database);
    t_room *room = mx_get_room("uchat", database);
    if (room == NULL) {
        printf("error room\n");
        exit(1);
    }
    printf("ID_ROMM -> \t%d\n", room->id);
    printf("NAME_ROOM -> \t%s\n", room->name);
    printf("CUSTOMER -> \t%s\n\n", room->customer);
    room = mx_get_room("Robert", database);
    if (room == NULL) {
        printf("error room\n");
        exit(1);
    }
    printf("ID_ROMM -> \t%d\n", room->id);
    printf("NAME_ROOM -> \t%s\n", room->name);
    printf("CUSTOMER -> \t%s\n\n", room->customer); 
    room = mx_get_room("kill", database);
    if (room == NULL) {
        printf("error\n");
        exit(1);
    }
    printf("ID_ROMM -> \t%d\n", room->id);
    printf("NAME_ROOM -> \t%s\n", room->name);
    printf("CUSTOMER -> \t%s\n\n", room->customer);
    room = mx_get_room("dolli", database);
    if (room == NULL) {
        printf("error\n");
        exit(1);
    }
    printf("ID_ROMM -> \t%d\n", room->id);
    printf("NAME_ROOM -> \t%s\n", room->name);
    printf("CUSTOMER -> \t%s\n\n", room->customer);

    printf("end test room !\n\n");
    mx_close_database(database);
}
