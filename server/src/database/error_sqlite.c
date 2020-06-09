#include "server.h"

void mx_error_sqlite(int rv, char *error, char *where_error) {
    if (rv != SQLITE_OK && rv != SQLITE_DONE && rv != SQLITE_ROW) {
        mx_logger(MX_LOG_FILE, LOGWAR, 
                  "rv -> (%d)\n error is here -> (%s)\n, error -> [%s]\n",
                  rv, error, where_error);
    }
}