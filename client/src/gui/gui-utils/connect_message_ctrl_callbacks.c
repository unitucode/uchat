#include "client.h"

static void req_delete_msg(GtkListBox *box, GtkListBoxRow *row, t_chat *chat) {
    t_gmsg *gmsg = (t_gmsg*)g_object_get_data(G_OBJECT(row), "gmsg");
    t_dtp *dtp = mx_del_msg_request(gmsg->room_id, gmsg->message_id);

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    (void)box;
}

void mx_delete_selected_msgs(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, MX_LOCAL_ROOMS);

    gtk_list_box_selected_foreach(groom->box_messages,
                                  (GtkListBoxForeachFunc)req_delete_msg,
                                  chat);
    (void)btn;
}

void mx_show_edit_msg(GtkButton *btn, t_chat *chat) {
    GObject *buffer = gtk_builder_get_object(chat->builder, "buffer_message");
    GObject *label_text = gtk_builder_get_object(chat->builder,
                                                 "label_edit_text");
    t_gmsg *msg = mx_get_selected_gmsg(chat->builder);
    gchar *old_text = g_strdelimit(g_strdup(msg->msg), "\n", ' ');

    chat->msg_placeholder = false;
    gtk_label_set_text(GTK_LABEL(label_text), old_text);
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer), msg->msg, -1);
    mx_switch_room_header(chat->builder, MX_ROOM_CTRL);
    g_free(old_text);
    (void)btn;
}

void mx_switch_to_msg_ctrl(GtkButton *btn, GtkBuilder *builder) {
    mx_switch_room_header(builder, MX_MSG_CTRL);
    (void)btn;
}

void mx_unselect_msg(GtkButton *btn, GtkBuilder *builder) {
    mx_unselect_curr_room_messages(builder);
    mx_switch_room_header(builder, MX_ROOM_CTRL);
    (void)btn;
}
