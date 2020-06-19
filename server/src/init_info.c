#include "server.h"

/*
 * Initializates chat variables
 */
t_info *mx_init_info(void) {
    t_info *info = mx_malloc(sizeof(t_info));

    info->users = NULL;
    info->database = mx_open_db(MX_DB);
    mx_init_receiver(info);
    srand(time(NULL));
    return info;
}

/*
 * Deinitializates chat variables
 */
void mx_deinit_info(t_info **info) {
    mx_close_database((*info)->database);
    free(*info);
    *info = NULL;
}
