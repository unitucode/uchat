#include "utils.h"

static cJSON *get_object_message(sqlite3_stmt *stmt) {
    cJSON *object_message = cJSON_CreateObject();

    cJSON_AddItemToObject(object_message, "id_message",  cJSON_CreateNumber(sqlite3_column_int(stmt, 0)));
    cJSON_AddItemToObject(object_message, "id_room",  cJSON_CreateNumber(sqlite3_column_int(stmt, 1)));
    cJSON_AddItemToObject(object_message, "login", cJSON_CreateString((char*)sqlite3_column_text(stmt, 2)));
    cJSON_AddItemToObject(object_message, "date",  cJSON_CreateNumber(sqlite3_column_int(stmt, 3)));
    cJSON_AddItemToObject(object_message, "message", cJSON_CreateString((char*)sqlite3_column_text(stmt, 4)));
    return object_message;
}

static cJSON *get_message_arr(char *name_room, unsigned int id_room, sqlite3 *database) {
    cJSON *arr_object = cJSON_CreateArray();
    sqlite3_str *str = sqlite3_str_new(database);
    sqlite3_stmt *stmt;
    char *sql = NULL;
    int ret_val = 0;
    
    sqlite3_str_appendall(str, "SELECT * FROM ");
    sqlite3_str_appendall(str, name_room);
    sqlite3_str_appendall(str, " WHERE ID_ROOM = ?1");
    sql = sqlite3_str_finish(str);
    ret_val = sqlite3_prepare_v3(database, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id_room);
    for (int i = 0; i < 30 && (ret_val = sqlite3_step(stmt)) == SQLITE_ROW; i++)
        cJSON_AddItemToArray(arr_object, get_object_message(stmt));
    sqlite3_free(sql);
    sqlite3_finalize(stmt);
    return arr_object;
}

static cJSON *get_data_room(unsigned int id_room, sqlite3 *database, sqlite3_stmt *stmt) {
    cJSON *object_tmp = cJSON_CreateObject();
    char *name_room = NULL;

    cJSON_AddItemToObject(object_tmp, "id_room",  cJSON_CreateNumber(sqlite3_column_int(stmt, 0)));
    name_room = strdup((char*)sqlite3_column_text(stmt, 1));
    cJSON_AddItemToObject(object_tmp, "name_room",  cJSON_CreateString(name_room));
    cJSON_AddItemToObject(object_tmp, "customer_login",  cJSON_CreateString((char*)sqlite3_column_text(stmt, 2)));
    cJSON_AddItemToObject(object_tmp, "message", get_message_arr(name_room, id_room, database));
    return object_tmp;
}

static cJSON *get_json(sqlite3 *database, t_id_room *id) {
    cJSON *object = cJSON_CreateObject();
    cJSON *rooms = cJSON_CreateArray();
    sqlite3_stmt *stmt;
    int ret_val;

    while (id != NULL) {
        ret_val = sqlite3_prepare_v3(database, "SELECT * FROM ROOMS WHERE id = ?1", -1, 0, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, id->id_room);
        ret_val = sqlite3_step(stmt);
        if (ret_val == 100)
            cJSON_AddItemToArray(rooms, get_data_room(id->id_room, database, stmt));
        id = id->next;
    }
    cJSON_AddItemToObject(object, "rooms", rooms);
    sqlite3_finalize(stmt);
    return object;
}


cJSON *mx_create_json_object(sqlite3 *database, char *user_login) {
    sqlite3_stmt *stmt;
    int ret_val;
    t_id_room *id = malloc(sizeof(t_id_room));
    t_id_room *save = id;
    
    id->id_room = 0;
    id->next = NULL;
    sqlite3_prepare_v3(database, "SELECT ID_ROOM FROM MEMBER WHERE login = ?1", -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, user_login, -1, SQLITE_STATIC);
    while ((ret_val = sqlite3_step(stmt)) == SQLITE_ROW) {
        if (id->id_room != 0) {
            id->next = malloc(sizeof(t_id_room));
            id = id->next;            
        }
        id->id_room = sqlite3_column_int(stmt, 0);
        id->next = NULL;
    }
    sqlite3_finalize(stmt);
    return get_json(database, save);
}
