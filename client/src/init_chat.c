#include "client.h"

t_chat *mx_init_chat(void) {
    t_chat *chat = mx_malloc(sizeof(t_chat));

    chat->builder = NULL;
    chat->ssl = NULL;
    return chat;
}
