#include "server.h"

/*
 * Initializates chat variables
 */
t_info *mx_init_info(void) {
    t_info *info = mx_malloc(sizeof(t_info));

    info->users = g_hash_table_new(g_str_hash, g_str_equal);
    info->database = mx_open_db(MX_DB);
    mx_init_receiver(info);
    srand(time(NULL));
    return info;
}

/*
 * Deinitializates chat variables
 */
void mx_deinit_info(t_info **info) {
    mx_close_db((*info)->database);
    free(*info);
    *info = NULL;
}
