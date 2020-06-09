#include "client.h"

void mx_init_gui(t_chat *chat) {
    mx_connect_authorization(chat);
    mx_connect_addroom(chat);
    mx_connect_send_message(chat);
}
