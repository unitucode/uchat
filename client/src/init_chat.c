#include "client.h"

t_chat *mx_init_chat(void) {
    t_chat *chat = mx_malloc(sizeof(t_chat));

    chat->builder = NULL;
    chat->ssl = NULL;
    chat->auth_token = NULL;
    chat->queue = g_async_queue_new();
    chat->valid = true;
    return chat;
}

// void mx_deinit_chat(t_chat **chat) {
//     mx_free
// }
