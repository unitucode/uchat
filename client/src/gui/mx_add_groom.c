#include "client.h"

void mx_add_groom(t_groom *room, t_chat *chat) {
    mx_add_messages_box(room, chat);
    mx_add_room_row(room, chat, MX_LOCAL_ROOMS);
}
