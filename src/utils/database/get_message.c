#include <utils.h>

static t_message *for_get_message(sqlite3_stmt *stmt) {
    int returnvalue;
    t_message *message = NULL;

    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_ROW) {
        mx_logger(MX_LOG_FILE, LOGERR, "not found message");
        return NULL;
    }
    message = malloc(sizeof(t_message));
    message->id_message = sqlite3_column_int(stmt, 0);
    message->login = strdup((const char*)sqlite3_column_text(stmt, 1));
    message->date = sqlite3_column_int(stmt, 2);
    message->json = strdup((const char*)sqlite3_column_text(stmt, 3));
    sqlite3_finalize(stmt);;
    return message;
}

t_message *mx_get_message_by_id(int id_message, sqlite3 *database) {
    int returnvalue;
    sqlite3_stmt *stmt;

    returnvalue = sqlite3_prepare_v3(database, "SELECT * FROM MESSAGE WHERE ID_MESSAGE = ?1", -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id_message);
    return for_get_message(stmt);
}

t_message *mx_get_message_by_login(char *login, sqlite3 *database) {
    int returnvalue;
    sqlite3_stmt *stmt;
    
    returnvalue = sqlite3_prepare_v3(database, "SELECT * FROM MESSAGE WHERE LOGIN = ?1", -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    return for_get_message(stmt);
}

// t_message *mx_message() {
    
// }  

