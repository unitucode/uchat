#include "client.h"

static gboolean handle(t_chat *chat) {
    
    return G_SOURCE_REMOVE;
}

void mx_handle_request(t_chat *chat) {
    g_idle_add(G_SOURCE_FUNC(handle), chat);
}
