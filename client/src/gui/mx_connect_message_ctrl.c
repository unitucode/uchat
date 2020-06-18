#include "client.h"

/*
 * CALLBACK for Glade
 */
void mx_switch_to_msg_ctrl(GtkButton *btn, GtkBuilder *builder) {
    mx_switch_room_header(builder, MX_MSG_CTRL);
    (void)btn;
}

void unselect_msg(GtkButton *btn, GtkBuilder *builder) {
    mx_unselect_curr_room_messages(builder);
    mx_switch_room_header(builder, MX_ROOM_CTRL);
    // mx_widget_set_visibility_by_name(builder, "btn_edit_msg", TRUE);
    (void)btn;
}

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
    mx_switch_room_header(builder, MX_ROOM_CTRL);
    (void)btn;
}

void mx_connect_message_ctrl(t_chat *chat) {
    GObject *btn_delete = gtk_builder_get_object(chat->builder,
                                                 "btn_delete_msg");
    GObject *btn_edit = gtk_builder_get_object(chat->builder,
                                               "btn_edit_msg");
    GObject *btn_unselect = gtk_builder_get_object(chat->builder,
                                                  "btn_unselect_msg");

    g_signal_connect(btn_delete, "clicked", G_CALLBACK(req_delete_msg), chat);
    g_signal_connect(btn_edit, "clicked",
                     G_CALLBACK(show_edit_msg), chat->builder);
    g_signal_connect(btn_unselect, "clicked",
                     G_CALLBACK(unselect_msg), chat->builder);
}
