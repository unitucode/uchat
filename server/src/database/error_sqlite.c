#include "server.h"

int mx_error_sqlite(int rv, char *error, char *where_error) {
    if (rv != SQLITE_OK && rv != SQLITE_DONE && rv != SQLITE_ROW) {
        mx_logger(MX_LOG_FILE, LOGWAR, 
                  "\nrv -> (%d)\nerror is here -> (%s)\nerror -> [%s]\n",
                  rv, where_error, error);
        return 1;
    }
    return 0;
}
