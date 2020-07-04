#include "client.h"

static void req_ban_member(GObject *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, MX_LOCAL_ROOMS);
    t_dtp *dtp = NULL;

    dtp = mx_ban_member_request(groom->id,
                                (guint64)g_object_get_data(btn, "member_id"));
    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
}

void mx_connect_ban_member(t_chat *chat) {
    GObject *btn = gtk_builder_get_object(chat->builder, "btn_ban");

    g_signal_connect(btn, "clicked", G_CALLBACK(req_ban_member), chat);
}
