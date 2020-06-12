#include "client.h"

static gboolean reconnect_on(t_chat *chat) {
    puts("reconnect on");
    chat++;
    return G_SOURCE_REMOVE;
}

static gboolean reconnect_off(t_chat *chat) {
    puts("reconnect off");
    chat++;
    return G_SOURCE_REMOVE;
}

static gboolean cannot_reconnect(t_chat *chat) {
    puts("cannot reconnect");
    chat++;
    return G_SOURCE_REMOVE;
}

bool mx_reconnect(t_chat *chat) {
    g_idle_add(G_SOURCE_FUNC(reconnect_on), chat);
    for (int i = 0; i < MX_RECONN_ATTEMPTS; i++) {
        mx_logger(MX_LOG_FILE, LOGMSG, "Attemp to reconnect[%d]\n", i);
        sleep(MX_RECONN_DELAY_S);
        if (mx_connect(chat)) {
            g_idle_add(G_SOURCE_FUNC(reconnect_off), chat);
            return true;
        }
    }
    mx_logger(MX_LOG_FILE, LOGMSG, "Cannot reconnect\n");
    g_idle_add(G_SOURCE_FUNC(cannot_reconnect), chat);
    return false;
}
