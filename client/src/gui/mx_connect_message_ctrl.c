#include "client.h"

static void req_delete_msg(GtkButton *btn, t_chat *chat) {
    t_gmsg *msg = mx_get_selected_gmsg(chat->builder);
    t_dtp *dtp = mx_del_msg_request(msg->room_id, msg->message_id);

    mx_send(chat->ssl, dtp);
    mx_free_request(&dtp);
    (void)btn;
}

static void show_edit_msg(GtkButton *btn, GtkBuilder *builder) {
    GObject *buffer = gtk_builder_get_object(builder, "buffer_message");
    GObject *label_text = gtk_builder_get_object(builder, "label_edit_text");
    t_gmsg *msg = mx_get_selected_gmsg(builder);

    gtk_label_set_text(GTK_LABEL(label_text), msg->msg); // DELETE ALL /n
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer), msg->msg, -1);
    (void)btn;
}

void mx_connect_message_ctrl(t_chat *chat) {
    GObject *btn_delete = gtk_builder_get_object(chat->builder,
                                                 "btn_delete_msg");
    GObject *btn_edit = gtk_builder_get_object(chat->builder,
                                               "btn_edit_msg");

    g_signal_connect(btn_delete, "clicked", G_CALLBACK(req_delete_msg), chat);
    g_signal_connect(btn_edit, "clicked",
                     G_CALLBACK(show_edit_msg), chat->builder);
}
