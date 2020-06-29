#include "client.h"

/*
 * Function: mx_get_data
 * -------------------------------
 * Sends request to get all rooms
 * 
 * chat: information about chat
 */
void mx_get_data(t_chat *chat) {
    t_dtp *get_rooms = mx_get_rooms_request(0);

    mx_send(chat->out, get_rooms);
}
