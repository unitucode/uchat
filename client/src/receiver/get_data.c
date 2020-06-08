#include "client.h"

void mx_get_data(t_chat *chat) {
    t_dtp *get_rooms = mx_get_rooms_request(0);

    mx_send(chat->ssl, get_rooms);
}
