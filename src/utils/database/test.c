#include "utils.h"

void mx_test_json() {
    sqlite3 *database =  mx_server_data_open(MX_DB_USER);
    mx_create_table_rooms(database);
    mx_create_table_member(database);
    mx_insert_room(database, "vlad", "chat_of_vlad");
    mx_create_table_room(database, "chat_of_vlad");
    mx_insert_memeber(database, 3, "vlad");
    mx_close_database(database);
    printf("Ok\n");
}

void mx_json() {
    sqlite3 *database =  mx_server_data_open(MX_DB_USER);
    t_room_messages *room = malloc(sizeof(t_room_messages));

    room->name_room = "chat_of_vlad";
    room->login = "vlad";
    room->date = 54;
    room->message = "hello world";
    mx_insert_to_room(database, room);
    mx_close_database(database);
    printf("Ok\n");
}

