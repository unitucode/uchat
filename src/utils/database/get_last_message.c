#include "utils.h"

t_message *mx_get_last_message(sqlite3 *database) { //id_room
    t_message *message = malloc(sizeof(t_message));
    t_message *save = message;
    sqlite3_stmt *stmt;
    int returnvalue = 0;

    message->json = NULL;
    returnvalue = sqlite3_prepare_v3(database, "SELECT * FROM MESSAGE ORDER BY date DESC", -1, 0, &stmt, NULL);
    printf("vlad -> %d\n", returnvalue);
    if (returnvalue != SQLITE_OK)
        mx_elogger(MX_LOG_FILE, LOGERR, "get data from message");
    for (int i = 0; i < 50 && (returnvalue = sqlite3_step(stmt)) == SQLITE_ROW; i++) {
        if (message->json != NULL) {
            message->next = malloc(sizeof(t_message));
            message = message->next;            
        }
        message->id_message = sqlite3_column_int(stmt, 0);
        message->login = strdup((const char*)sqlite3_column_text(stmt, 1));
        message->date = sqlite3_column_int(stmt, 2);
        message->json = strdup((const char*)sqlite3_column_text(stmt, 3));
        message->next = NULL;
    }
    if (message->json == NULL) {
        mx_free((void**)message);
        message = NULL;
        return NULL;
    }
    return save;
}
