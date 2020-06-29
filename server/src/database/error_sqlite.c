#include "server.h"

/*
 * Function: 
 * 
 */

gboolean mx_error_sqlite(gint32 rv, gchar *error, gchar *where_error) {
    if (rv != SQLITE_OK && rv != SQLITE_DONE && rv != SQLITE_ROW) {
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_WARNING, "error database");
        return true;
    }
    error++;
    where_error++;
    return false;
}
