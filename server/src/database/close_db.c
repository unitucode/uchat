#include "server.h"

void mx_close_db(sqlite3 *db) {
    gint32 rv = sqlite3_close(db);

    if (rv != SQLITE_OK){
        printf("stan -> %d\n", rv);
        mx_logger(MX_LOG_FILE, LOGWAR, "close database");
    }
}
