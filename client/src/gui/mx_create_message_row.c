#include "client.h"

GtkWidget *mx_create_message_row(t_chat *chat, t_gmsg *gmsg) {
    gboolean is_own = !g_strcmp0(chat->login, gmsg->login);
    GtkWidget *eventbox = NULL;

    if (is_own)
        eventbox = mx_create_own_message_row(chat->builder, gmsg);
    else
        eventbox = mx_create_reg_message_row(chat->builder, gmsg);
    return eventbox;
}
