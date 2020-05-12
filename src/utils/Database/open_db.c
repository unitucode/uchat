#include <utils.h>

sqlite3 *mx_server_data_open(char *name_db) {
    sqlite3 *database;
    int tmp;

    if ((tmp = sqlite3_open(name_db, &database)) == SQLITE_OK) {
        return database;
    }
    // mx_logger(MX_LOG_FILE, LOGWAR, "error conect database");
    return database;
}
