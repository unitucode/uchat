#include "server.h"

static cJSON *get_object_message(sqlite3_stmt *stmt) {
    cJSON *o_m = cJSON_CreateObject();

    cJSON_AddNumberToObject(o_m, "user_id", sqlite3_column_int64(stmt, 0));
    cJSON_AddNumberToObject(o_m, "room_id", sqlite3_column_int64(stmt, 1));
    cJSON_AddNumberToObject(o_m, "message_id", sqlite3_column_int64(stmt, 2));
    cJSON_AddNumberToObject(o_m, "date", sqlite3_column_int64(stmt, 3));
    cJSON_AddStringToObject(o_m, "message",
                            MX_J_STR((char*)sqlite3_column_text(stmt, 4)));
    cJSON_AddNumberToObject(o_m, "type", sqlite3_column_int(stmt, 5));
    cJSON_AddNumberToObject(o_m, "file_size", sqlite3_column_int(stmt, 6));
    cJSON_AddStringToObject(o_m, "file_name",
                            MX_J_STR((char*)sqlite3_column_text(stmt, 7)));
    cJSON_AddNumberToObject(o_m, "status", sqlite3_column_int(stmt, 8));
    cJSON_AddNumberToObject(o_m, "date_dead", sqlite3_column_int(stmt, 9));
    return o_m;
}

static cJSON *get_messages_by_id(sqlite3_stmt *stmt, guint64 room_id, 
                                 gint64 count, guint64 date) {
    cJSON *room = cJSON_CreateObject();
    cJSON *message = cJSON_CreateArray();
    gint32 rv = 0;

    sqlite3_bind_int64(stmt, 1, date);
    for (gint64 i = 0; i < count 
                        && (rv = sqlite3_step(stmt)) == SQLITE_ROW; i++) {
        cJSON_AddItemToArray(message, get_object_message(stmt));
    }
    cJSON_AddItemToObject(room, "room_id", cJSON_CreateNumber(room_id));
    cJSON_AddItemToObject(room, "messages", message);
    sqlite3_finalize(stmt);
    return room;
}

cJSON *mx_get_new_messages_by_id(sqlite3 *db, guint64 room_id, guint64 date,
                                 gint64 count) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;
    gchar *request = mx_create_request_message_by_id(db, room_id,
                                                     DB_NEW_MESSAGE);

    printf("%s\n", request);
    sqlite3_prepare_v2(db, request, -1, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "get_new_msg");
    sqlite3_free(request);
    return get_messages_by_id(stmt, room_id, count, date);
}

cJSON *mx_get_old_messages_by_id(sqlite3 *db, guint64 room_id, guint64 date, 
                                 gint64 count) {
    sqlite3_stmt *stmt;
    gchar *request = mx_create_request_message_by_id(db, room_id, 
                                                     DB_OLD_MESSAGE);

    mx_error_sqlite(sqlite3_prepare_v2(db, request, -1, &stmt, NULL), 
                    "prepare", "get old messages");
    printf("%s\n%llu\n", request, date);
    sqlite3_free(request);
    return get_messages_by_id(stmt, room_id, count, date);
}

cJSON *mx_get_curr_messages_by_id(sqlite3 *db, guint64 room_id, gint64 count) {
    sqlite3_stmt *stmt;
    gchar *request = mx_create_request_message_by_id(db, room_id, 
                                                     DB_CURR_MESSAGE);

    mx_error_sqlite(sqlite3_prepare_v2(db, request, -1, &stmt, NULL), "prepare", "get curr message");
    sqlite3_free(request);
    return get_messages_by_id(stmt, room_id, count, 0);
}
