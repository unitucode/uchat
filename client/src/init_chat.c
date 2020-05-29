#include "client.h"

t_chat *mx_init_chat(void) {
    t_chat *chat = mx_malloc(sizeof(t_chat));

    chat->builder = NULL;
    chat->ssl = NULL;
    chat->auth_token = NULL;
    return chat;
}

// void mx_deinit_chat(t_chat **chat) {
//     mx_free
// }
