#include "utils.h"

sqlite3 *mx_server_data_open(char *name) {
    sqlite3 *database;
    int tmp;    

    if ((tmp = sqlite3_open("database.db", &database)) == SQLITE_OK) { 
        return database;
    }
    mx_logger(MX_LOG_FILE, LOGWAR, "database error conect");
    return NULL;
}
