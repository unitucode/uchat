#include "client.h"

void mx_init_gui(t_chat *chat) {
    mx_connect_authorization(chat);
    mx_connect_addroom(chat);
    mx_connect_send_message(chat);
    mx_connect_profile_settings(chat);
    mx_connect_room_settings(chat);
    mx_connect_message_ctrl(chat);
    mx_connect_test_request(chat); // DELETE
}
