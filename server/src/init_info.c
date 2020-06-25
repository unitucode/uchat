#include "server.h"

/*
 * Function: mx_init_info
 * -------------------------------
 * Creates information about another users, database for all clients
 * 
 * returns: new information
 */
t_info *mx_init_info(void) {
    t_info *info = mx_malloc(sizeof(t_info));

    info->users = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);
    info->database = mx_open_db(MX_DB);
    mx_init_receiver(info);
    return info;
}

/*
 * Function: mx_deinit_info
 * -------------------------------
 * Closes database, deletes all used memory
 * 
 * info: pointer to information
 */
void mx_deinit_info(t_info **info) {
    mx_close_db((*info)->database);
    g_hash_table_destroy((*info)->users);
    free(*info);
    *info = NULL;
}
