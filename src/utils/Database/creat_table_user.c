#include <utils.h>

void mx_creat_table_user(sqlite3 *db_user) {
    char *sql = "CREATE TABLE USER("  \
                "ID             INTEGER PRIMARY KEY NOT NULL," \
                "TOKEN          TEXT    NOT NULL," \
                "LOGIN          TEXT    NOT NULL," \
                "PASSWORD       TEXT    NOT NULL );";
    sqlite3_exec(db_user, sql, 0, 0, 0);
    // printf("%d\n", returnvalues);
    // if (returnvalues != SQLITE_OK) {
    //     printf("vlad");
    //     mx_elogger(MX_LOG_FILE, LOGWAR, "error creat database table");
    // }
}

