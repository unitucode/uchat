#include <utils.h>

void mx_create_table_room(sqlite3 *db_user) {
    char *sql = "CREATE TABLE ROOM("  \
                "ID             INTEGER PRIMARY KEY NOT NULL," \
                "ID_MESSAGE     INGEGER NOT NULL"  \
                "LOGIN          TEXT    NOT NULL," \
                "MESSAGE        TEXT    NOT NULL," \
                "DATE           TEXT    NOT NULL);";
    int tmp = 0;

    if ((tmp = sqlite3_exec(db_user, sql, 0, 0, 0)) != SQLITE_OK) {
        // printf("tmp create -> %d\n", tmp);
        // mx_elogger(MX_LOG_FILE, LOGWAR, "error create database table");
    }
}
