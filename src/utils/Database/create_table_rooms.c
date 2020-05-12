#include <utils.h>

void mx_create_table_rooms(sqlite3 *db_user) {
    char *sql = "CREATE TABLE ROOMS("  \
                "ID             INTEGER PRIMARY KEY NOT NULL," \
                "NAME           TEXT    NOT NULL);";
    int tmp = 0;

    if ((tmp = sqlite3_exec(db_user, sql, 0, 0, 0)) != SQLITE_OK) {
        // printf("tmp create -> %d\n", tmp);
        // mx_elogger(MX_LOG_FILE, LOGWAR, "error create database table");
    }
}
