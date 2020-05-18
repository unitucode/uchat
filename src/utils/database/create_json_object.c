#include "utils.h" 

static cJSON *get_json(sqlite3 *database, t_id_room *id) {
    cJSON *object = cJSON_CreateObject();
    cJSON *rooms = cJSON_CreateArray();
    char *name_room = NULL;
    printf("Ok\n");
    sqlite3_stmt *stmt;
    while (id != NULL) {
        printf("id -> %d\n", id->id_room);
        cJSON *object_tmp = cJSON_CreateObject();
        cJSON *id_message = cJSON_CreateArray();
        cJSON *login = cJSON_CreateArray();
        cJSON *date = cJSON_CreateArray();
        cJSON *message = cJSON_CreateArray();
        sqlite3_str *str = sqlite3_str_new(database);
        char *sql = NULL;
        int ret_val;

        ret_val = sqlite3_prepare_v3(database, "SELECT * FROM ROOMS WHERE id = ?1", -1, 0, &stmt, NULL);
        printf("Ok -> (%d)\n", ret_val);
        sqlite3_bind_int(stmt, 1, id->id_room);
        ret_val = sqlite3_step(stmt);
        if (ret_val == 101) {
            id = id->next;
            break;
        }
        printf("Ok -> (%d)\n", ret_val);
        cJSON_AddItemToObject(object_tmp, "id_room",  cJSON_CreateNumber(sqlite3_column_int(stmt, 0)));
        name_room = strdup((char*)sqlite3_column_text(stmt, 1));
        printf("Ok\n");
        printf("name -> %s\n", name_room);
        cJSON_AddItemToObject(object_tmp, "name_room",  cJSON_CreateString(name_room));
        cJSON_AddItemToObject(object_tmp, "customer_login",  cJSON_CreateString((char*)sqlite3_column_text(stmt, 2)));
        // sqlite3_finalize(stmt);        
        sqlite3_str_appendall(str, "SELECT * FROM ");
        sqlite3_str_appendall(str, "chat_of_vlad");
        sql = sqlite3_str_finish(str);
        printf("%s\n", sql);
        ret_val = sqlite3_prepare_v3(database, sql, -1, 0, &stmt, NULL);
        printf("%d\n", ret_val);
        while ((ret_val = sqlite3_step(stmt)) == SQLITE_ROW) {
            printf("statrt\n");
            cJSON_AddItemToArray(id_message,  cJSON_CreateNumber(sqlite3_column_int(stmt, 0)));
            cJSON_AddItemToArray(login, cJSON_CreateString((char*)sqlite3_column_text(stmt, 1)));
            cJSON_AddItemToArray(date,  cJSON_CreateNumber(sqlite3_column_int(stmt, 2)));
            cJSON_AddItemToArray(message, cJSON_CreateString((char*)sqlite3_column_text(stmt, 3)));
        }
        cJSON_AddItemToObject(object_tmp, "id_message", id_message);
        cJSON_AddItemToObject(object_tmp, "login",  login);
        cJSON_AddItemToObject(object_tmp, "date",  date);
        cJSON_AddItemToObject(object_tmp, "message",  message);
        char *string = cJSON_Print(object_tmp);
        printf("%s\n", string);
        cJSON_AddItemToArray(rooms, object_tmp);
        sqlite3_free(sql);
        sqlite3_finalize(stmt);
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
    printf("Ok\n");
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
