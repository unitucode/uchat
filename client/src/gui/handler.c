#include "client.h"

static gboolean handle(t_chat *chat) {
    t_dtp *dtp = NULL;

    while ((dtp = (t_dtp*)g_async_queue_try_pop(chat->queue))
           && chat->valid) {
        puts("handle");
        if (chat->auth_token || dtp->type == RQ_ERROR_MSG
            || dtp->type == RQ_TOKEN || dtp->type == RQ_RECONNECT) {
            if (chat->request_handler[dtp->type]) {
                if (!chat->request_handler[dtp->type](dtp, chat)) {
                    shutdown(SSL_get_fd(chat->ssl), SHUT_WR);
                    chat->valid = false;
                }
            }
        }
        else
            chat->valid = false;
        mx_free_request(&dtp);
    }
    return G_SOURCE_REMOVE;
}

void mx_handle_request(t_chat *chat) {
    g_idle_add(G_SOURCE_FUNC(handle), chat);
}
