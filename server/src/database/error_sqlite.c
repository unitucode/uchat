#include "server.h"

gboolean mx_error_sqlite(gint32 rv, gchar *error, gchar *where_error) {
    if (rv != SQLITE_OK && rv != SQLITE_DONE && rv != SQLITE_ROW) {
        mx_logger(MX_LOG_FILE, LOGERR, 
                  "\nrv -> (%d)\nerror is here -> (%s)\nerror -> [%s]\n",
                  rv, where_error, error);
        return true;
    }
    return false;
}
