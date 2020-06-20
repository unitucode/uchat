#include "server.h"

gboolean mx_user_contains(sqlite3 *db, guint64 user_id, guint64 room_id) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "select * from members where user_id = ?1 "
                                "and room_id = ?2", -1, &stmt, 0);
    mx_error_sqlite(rv, "prepare", "user contains");
    sqlite3_bind_int64(stmt, 1, user_id);
    sqlite3_bind_int64(stmt, 2, room_id);
    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return true;
    }
    mx_error_sqlite(rv, "step", "user contains");
    sqlite3_finalize(stmt);
    return false;
}

cJSON *mx_users_of_room_in_json(GList *list) {
    cJSON *array_j = cJSON_CreateArray();

    while (list != NULL) {
        cJSON_AddItemToArray(array_j, cJSON_CreateString((gchar*)list->data));
        list = list->next;
    }
    return array_j;
}

void mx_destroy_data(gpointer data) {
    g_free(data);
}

GList *mx_get_users_in_room(sqlite3 *db, guint64 room_id) {
    sqlite3_stmt *stmt;
    gint rv = SQLITE_OK;
    GList *list = NULL;

    rv = sqlite3_prepare_v2(db, "select distinct login from users inner join "
                                "members on users.id = members.user_id where "
                                "room_id = ?1",
                            -1, &stmt, 0);
    mx_error_sqlite(rv, "prepare", "get_users_in_room");
    sqlite3_bind_int64(stmt, 1, room_id);
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        list = g_list_append(list,
                             (gpointer)strdup((char*)sqlite3_column_text(stmt,
                                                                         0)));
    mx_error_sqlite(rv, "step", "get_users_in_room");
    sqlite3_finalize(stmt);
    return list;
}

void mx_edit_members(sqlite3 *db, guint64 room_id, guint64 user_id,
                       gint8 new_perm) {
    sqlite3_str *sqlite_str = sqlite3_str_new(db);
    gchar *request = NULL;
    gint32 rv = SQLITE_OK;

    sqlite3_str_appendf(sqlite_str, "update members set permission = %d where room_id = "
                        "%llu and user_id = %llu", new_perm, room_id, user_id);
    request = sqlite3_str_finish(sqlite_str);
    rv = sqlite3_exec(db, request, 0, 0, 0);
    mx_error_sqlite(rv, "exec", "edit members");
    sqlite3_free(request);
}

// void mx_delete_members(sqlite3 *db, guint64 room_id, guint64 user_id) {

// }