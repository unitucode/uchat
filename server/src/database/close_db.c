#include "utils.h"

void mx_close_database(sqlite3 *database) {
    int stan = sqlite3_close(database);

    if (stan != SQLITE_OK){
        printf("stan -> %d\n", stan);
        mx_logger(MX_LOG_FILE, LOGWAR, "close database");
    }
}
