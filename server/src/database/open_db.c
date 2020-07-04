#include "server.h"

/*
 * Function: mx_open_db
 * -------------------------------
 * open or create database
 * 
 * name_db: the name of the database you want to open
 */
sqlite3 *mx_open_db(gchar *name_db) {
    sqlite3 *db;

    if (sqlite3_open(name_db, &db) != SQLITE_OK)
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_WARNING, "error open database");
    mx_create_table(db);
    return db;
}

