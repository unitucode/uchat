#include "client.h"

static gboolean handle(t_chat *chat) {
    t_dtp *dtp = NULL;
    gboolean result = G_SOURCE_REMOVE;

    while ((dtp = (t_dtp*)g_async_queue_try_pop(chat->queue))) {
        puts("handle");
        if (chat->auth_token
            || dtp->type == RQ_ERROR_MSG
            || dtp->type == RQ_TOKEN) {
            if (chat->request_handler[dtp->type]) {
                if (!chat->request_handler[dtp->type](dtp, chat)) {
                    shutdown(SSL_get_fd(chat->ssl), SHUT_WR);
                    //error packet
                    result = G_SOURCE_REMOVE;
                }
            }
        }
        else {
            result = G_SOURCE_REMOVE;
        }
        mx_free_request(&dtp);
    }
    return result;
}

void mx_handle_request(t_chat *chat) {
    g_idle_add(G_SOURCE_FUNC(handle), chat);
}
