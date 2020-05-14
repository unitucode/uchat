#include <utils.h>

void mx_create_table(char *table, sqlite3 *database) {
    int tmp = 0;

    if ((tmp = sqlite3_exec(database, table, 0, 0, 0)) != SQLITE_OK) {
        // printf("tmp create -> %d\n", tmp);
        // mx_elogger(MX_LOG_FILE, LOGWAR, "error create database table");
    }
}
