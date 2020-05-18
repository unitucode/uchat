#include "utils.h"

// void mx_test_test() {

// }
void mx_test_users() {
    printf("start test users !\n\n");
    sqlite3 *database = mx_server_data_open(MX_DB_USER);
    mx_create_table_users(database);
    mx_insert_user(database, "vlad", "uchat", "token");
//     mx_insert_user("sasha", "kill", "token", database);
//     mx_insert_user("ura", "dolli", "token", database);
//     mx_insert_user("pasha", "Robert", "token", database);
    t_user *user = mx_get_user_by_login(database, "vlad");
    if (user == NULL) {
        printf("error user\n");
        exit(1);
    }
    printf("LOGIN -> \t%s\n", user->login);
    printf("PASS -> \t%s\n", user->password);
    printf("TOKEN -> \t%s\n", user->token);
    printf("PERMISSION -> \t%d\n\n", user->permission);

//     user = mx_get_user_by_login("sasha", database);
//     if (user == NULL) {
//         printf("error user\n");
//         exit(1);
//     }
//     printf("LOGIN -> \t%s\n", user->login);
//     printf("PASS -> \t%s\n", user->password);
//     printf("TOKEN -> \t%s\n", user->token);
//     printf("PERMISSION -> \t%d\n\n", user->permission);

//     user = mx_get_user_by_login("ura", database);
//     if (user == NULL) {
//         printf("error user\n");
//         exit(1);
//     }
//     printf("LOGIN -> \t%s\n", user->login);
//     printf("PASS -> \t%s\n", user->password);
//     printf("TOKEN -> \t%s\n", user->token);
//     printf("PERMISSION -> \t%d\n\n", user->permission);
    
//     user = mx_get_user_by_login("pasha", database);
//     if (user == NULL) {
//         printf("error user \n");
//         exit(1);
//     }
//     printf("LOGIN -> \t%s\n", user->login);
//     printf("PASS -> \t%s\n", user->password);
//     printf("TOKEN -> \t%s\n", user->token);
//     printf("PERMISSION -> \t%d\n\n", user->permission);
//     mx_close_database(database);
//     printf("end test users !\n\n");
}

void mx_test_message() {
    printf("start test message !\n\n");
    sqlite3 *database = mx_server_data_open(MX_DB_USER);
    mx_create_table_message(database);
    mx_insert_message(database, "vlad", 6333, "json");
    mx_insert_message(database, "sasha", 7333, "json");
    mx_insert_message(database, "ura", 474444, "json");
    mx_insert_message(database, "pasha", 544472, "json");
    mx_insert_message(database, "vlad", 12456, "json");
    mx_insert_message(database, "sasha", 1552562, "json");
    mx_insert_message(database, "ura", 123358, "json");
    mx_insert_message(database, "pasha", 1549, "json");
    mx_insert_message(database, "vlad", 24550, "json");
    mx_insert_message(database, "sasha", 2555441, "json");
    mx_insert_message(database, "ura", 25225, "json");
    mx_insert_message(database, "pasha", 225223, "json");
    mx_insert_message(database, "vlad", 225565, "json");
    mx_insert_message(database, "sasha", 22564, "json");
    mx_insert_message(database, "ura", 32451, "json");
    mx_insert_message(database, "pasha", 427754, "json");
    mx_insert_message(database, "vlad", 27729, "json");
    mx_insert_message(database, "sasha", 22245, "json");
    mx_insert_message(database, "ura", 262242, "json");
    mx_insert_message(database, "pasha", 312342, "json");
    mx_insert_message(database, "vlad", 32713245, "json");
    mx_insert_message(database, "sasha", 335226, "json");
    mx_insert_message(database, "ura", 323243, "json");
    mx_insert_message(database, "pasha", 42433, "json");
    t_message *message = mx_get_last_message(database);
    if (message == NULL) {
        printf("error message\n");
        exit(1);
    }  
    while (message) {
        printf("\tID -> \t%d", message->id_message);
        printf("\tLOG -> \t%s", message->login);
        printf("\tJSON -> \t%s", message->json);
        printf("\tDATE -> \t%lld\n", message->date);
        message = message->next;
    }
//     printf("ID_MESSAGE -> \t%d\n", message->id_message);
//     printf("LOGIN -> \t%s\n", message->login);
//     printf("JSON -> \t%s\n", message->json);
//     printf("DATE -> \t%lld\n\n", message->date);
//     message = mx_get_message_by_login("sasha", database);
//     if (message == NULL) {
//         printf("error message\n");
//         exit(1);
//     }
//     printf("ID_MESSAGE -> \t%d\n", message->id_message);
//     printf("LOGIN -> \t%s\n", message->login);
//     printf("JSON -> \t%s\n", message->json);
//     printf("DATE -> \t%lld\n\n", message->date);
//     message = mx_get_message_by_login("ura", database);
//     if (message == NULL) {
//         printf("error message\n");
//         exit(1);
//     }
//     printf("ID_MESSAGE -> \t%d\n", message->id_message);
//     printf("LOGIN -> \t%s\n", message->login);
//     printf("JSON -> \t%s\n", message->json);
//     printf("DATE -> \t%lld\n\n", message->date);
//     message = mx_get_message_by_login("pasha", database);
//     if (message == NULL) {
//         printf("error message\n");
//         exit(1);
//     }
//     printf("ID_MESSAGE -> \t%d\n", message->id_message);
//     printf("LOGIN -> \t%s\n", message->login);
//     printf("JSON -> \t%s\n", message->json);
//     printf("DATE -> \t%lld\n\n", message->date);
//     mx_close_database(database);
//     printf("end test message !\n\n");
}

// void mx_test_member() {
//     printf("start test member !\n\n");
//     sqlite3 *database = mx_server_data_open(MX_DB_USER);
//     mx_create_table(MX_MEMBER_TABLE, database);    
//     mx_insert_memeber(1, "vlad", database);
//     mx_insert_memeber(2, "sasha", database);
//     mx_insert_memeber(3, "pasha", database);
//     mx_insert_memeber(4, "ura", database);
//     printf("end test member !\n\n");
// }
static void insert_room(sqlite3 *database, char *customer, char *name_room) {
    sqlite3_stmt *stmt;
    int returnvalue = 0;

    returnvalue = sqlite3_prepare_v3(database, "INSERT INTO VLAD_ROOM(NAME_ROOM, CUSTOMER_LOGIN) VALUES(?1, ?2);", -1, 0, &stmt, NULL);
    if (returnvalue == SQLITE_ERROR)
        mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
     sqlite3_bind_text(stmt, 1, name_room, -1, SQLITE_STATIC);
     sqlite3_bind_text(stmt, 2, customer, -1, SQLITE_STATIC);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_DONE)
         mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    sqlite3_finalize(stmt);
}

static t_room *get_room(sqlite3 *database, char *name_room) {
    t_room *room = NULL;
    int returnvalue;
    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(database, "SELECT * FROM VLAD_ROOM WHERE name_room = ?1", -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, name_room, -1, SQLITE_STATIC);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_ROW) {
        printf("error get room\n");
        sqlite3_finalize(stmt);
        // mx_free((void**)room);
        return NULL;
    }
    room = malloc(sizeof(t_room));
    room->id = sqlite3_column_int(stmt, 0);
    room->name = strdup((const char*)sqlite3_column_text(stmt, 1));
    room->customer = strdup((const char*)sqlite3_column_text(stmt, 2));
    sqlite3_finalize(stmt);
    return room;
}

void mx_test_room() {
    printf("start test room !\n\n");
    sqlite3 *database = mx_server_data_open(MX_DB_USER);
    int tmp = 0;
    sqlite3_stmt *stmt;

    tmp = sqlite3_prepare_v3(database, "CREATE TABLE :f("  \
                       "ID                 INTEGER PRIMARY KEY NOT NULL," \
                       "NAME_ROOM          TEXT                NOT NULL, " \
                       "CUSTOMER_LOGIN     TEXT                NOT NULL);", -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 'f', "VLAD_ROOM", -1, SQLITE_STATIC);
    printf("tmp -> %d\n", tmp);
    tmp = sqlite3_step(stmt);
    printf("tmp -> %d\n", tmp);
    sqlite3_finalize(stmt);
    insert_room(database, "vlad", "room_of_vlad");
    t_room *room = get_room(database, "room_of_vlad");
    printf("ID -> \t%d\n", room->id);
    printf("NAME -> \t%s\n", room->name);
    printf("CUST -> \t%s\n", room->customer);
    printf("end test room\n");
    exit(1);
}

    // int returnvalue = 0;
    // sqlite3_stmt *stmt;

    // id_room++;
    // sqlite3_exec(database, "CREATE TABLE MEMBER("\
    //                         "ID_ROOM  INTEGER PRIMARY KEY NOT NULL,"\
    //                         "LOGIN    TEXT                NOT NULL);", 0, 0, 0);
    // returnvalue = sqlite3_prepare_v3(database, "INSERT INTO MEMBER(ID_ROOM, LOGIN)VALUES(3, json_object('a', 3, 'c', 4));", -1, 0, &stmt, NULL);
    // sqlite3_step(stmt);
    // sqlite3_finalize(stmt);
    // sqlite3_prepare_v3(database, "SELECT json_extract(member.login, '$') FROM MEMBER", -1, 0, &stmt, NULL);
    // sqlite3_step(stmt);
    // printf("(%d)\n", sqlite3_column_int(stmt, 0));
    // char *str = (char *)sqlite3_column_text(stmt, 0);
    // printf("(%s)\n", str);
    // sqlite3_finalize(stmt);
    // char *str = json_object('a', 2, 'c', 4);
    // printf("%s\n", str);
    // return str; 
    // return NULL;
