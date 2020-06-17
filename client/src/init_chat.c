#include "client.h"

t_chat *mx_init_chat(void) {
    t_chat *chat = mx_malloc(sizeof(t_chat));

    chat->builder = NULL;
    chat->curr_room = NULL;
    chat->auth_token = NULL;
    chat->queue = g_async_queue_new();
    chat->to_send = g_async_queue_new();
    chat->valid = true;
    chat->login = NULL;
    return chat;
}
