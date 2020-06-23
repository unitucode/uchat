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
    (void)btn;
}

static void req_delete_msg(GtkListBox *box, GtkListBoxRow *row, t_chat *chat) {
    t_gmsg *gmsg = (t_gmsg*)g_object_get_data(G_OBJECT(row), "gmsg");
    t_dtp *dtp = mx_del_msg_request(gmsg->room_id, gmsg->message_id);

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    (void)box;
}

static void delete_selected_msgs(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder,  MX_LOCAL_ROOMS);

    gtk_list_box_selected_foreach(groom->box_messages,
                                  (GtkListBoxForeachFunc)req_delete_msg,
                                  chat);
    (void)btn;
}

static void show_edit_msg(GtkButton *btn, GtkBuilder *builder) {
    GObject *buffer = gtk_builder_get_object(builder, "buffer_message");
    GObject *label_text = gtk_builder_get_object(builder, "label_edit_text");
    t_gmsg *msg = mx_get_selected_gmsg(builder);
    gchar *old_text = g_strdelimit(g_strdup(msg->msg), "\n", ' ');  

    gtk_label_set_text(GTK_LABEL(label_text), old_text);
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer), msg->msg, -1);
    mx_text_buffer_set_tags(GTK_TEXT_BUFFER(buffer));
    mx_format_text(GTK_TEXT_BUFFER(buffer));
    mx_switch_room_header(builder, MX_ROOM_CTRL);
    g_free(old_text);
    (void)btn;
}

void mx_connect_message_ctrl(t_chat *chat) {
    GObject *btn_delete = gtk_builder_get_object(chat->builder,
                                                 "btn_delete_msg");
    GObject *btn_edit = gtk_builder_get_object(chat->builder,
                                               "btn_edit_msg");
    GObject *btn_unselect = gtk_builder_get_object(chat->builder,
                                                  "btn_unselect_msg");

    g_signal_connect(btn_delete, "clicked",
                     G_CALLBACK(delete_selected_msgs), chat);
    g_signal_connect(btn_edit, "clicked",
                     G_CALLBACK(show_edit_msg), chat->builder);
    g_signal_connect(btn_unselect, "clicked",
                     G_CALLBACK(unselect_msg), chat->builder);
}
