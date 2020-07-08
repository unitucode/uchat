#include "server.h"

/*
 * Function: mx_free_user
 * -------------------------------
 * free struct t_db_user
 * 
 * user: structure t_db_user created with g_malloc
 */
void mx_free_user(t_db_user **user) {
    if (!user || !*user)
        return;
    if ((*user)->login)
        g_free((*user)->login);
    if ((*user)->pass)
        g_free((*user)->pass); 
    if ((*user)->token) 
        g_free((*user)->token);
    if ((*user)->desc)
        g_free((*user)->desc);
    if ((*user)->name)
        g_free((*user)->name);
    mx_free((gpointer)user);
    *user = NULL;
}

/*
 * Function: mx_free_room
 * -------------------------------
 * free struct t_db_room
 * 
 * room: structure t_db_room created with g_malloc
 */
void mx_free_room(t_db_room **room) {
    if (!room || !*room)
        return;
    if ((*room)->room_name)
        g_free((*room)->room_name);
    if ((*room)->desc)
        g_free((*room)->desc);
    mx_free((void **)room);
    room = NULL;
}

/*
 * Function: mx_free_message
 * -------------------------------
 * free struct t_db_message
 * 
 * message: structure t_db_message created with g_malloc
 */
void mx_free_message(t_db_message **message) {
    if (!message || !*message)
        return;
    if ((*message)->message)
        g_free((*message)->message);
    if ((*message)->file_name)
        g_free((*message)->file_name);
    mx_free((void **)message);
    message = NULL;
}
