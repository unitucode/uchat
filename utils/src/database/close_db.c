#include "utils.h"

void mx_close_database(sqlite3 *database) {
    int stan = sqlite3_close(database);

    if (stan != SQLITE_OK) {
        mx_elogger(MX_LOG_FILE, LOGERR, "error close database");
    }
}
