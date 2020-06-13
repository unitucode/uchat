#include "client.h"

static void req_msg_delete(GtkButton *btn, t_chat *chat) {
    t_gmsg *msg = mx_get_selected_gmsg(chat->builder);
    t_dtp *dtp = mx_del_msg_request(msg->room_id, msg->message_id);

    mx_send(chat->ssl, dtp);
    mx_free_request(&dtp);
    (void)btn;
}

void mx_connect_message_ctrl(t_chat *chat) {
    GObject *btn_delete = gtk_builder_get_object(chat->builder,
                                                 "btn_delete_msg");

    g_signal_connect(btn_delete, "clicked", G_CALLBACK(req_msg_delete), chat);
}
