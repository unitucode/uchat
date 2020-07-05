#include "client.h"

void mx_go_down(GtkButton *btn, GtkBuilder *builder) {
    t_groom *groom = mx_get_selected_groom(builder, MX_LOCAL_ROOMS);
    GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(groom->page);

    gtk_adjustment_set_value(adj, gtk_adjustment_get_upper(adj));
    (void)btn;
}

void mx_req_send_message(GtkButton *btn, t_chat *chat) {
    gchar *message_text = mx_get_buffer_text("buffer_message", chat->builder);
    t_groom *room = mx_get_selected_groom(chat->builder,  MX_LOCAL_ROOMS);
    t_dtp *dtp = NULL;

    g_strstrip(message_text);
    if (room && !chat->msg_placeholder && strlen(message_text) > 0) {
        mx_trim_message(&message_text);
        dtp = mx_msg_request(message_text, room->id);
        mx_send(chat->out, dtp);
        mx_free_request(&dtp);
        mx_clear_buffer_text("buffer_message", chat->builder);
    }
    g_free(message_text);
    mx_reset_messege_room(NULL, chat->builder);
    (void)btn;
}

void mx_req_edit_message(GtkButton *btn, t_chat *chat) {
    t_gmsg *gmsg = mx_get_selected_gmsg(chat->builder);
    gchar *new_text = mx_get_buffer_text("buffer_message", chat->builder);
    t_dtp *dtp = NULL;

    g_strstrip(new_text);
    if (strcmp(gmsg->msg, new_text) && strlen(new_text) > 0) {
        mx_trim_message(&new_text);
        dtp = mx_edit_msg_request(new_text, gmsg->room_id, gmsg->message_id);
        mx_send(chat->out, dtp);
        mx_free_request(&dtp);
    }
    else
        mx_switch_room_header(chat->builder, MX_MSG_CTRL);
    mx_clear_buffer_text("buffer_message", chat->builder);
    mx_hide_msg_editing(NULL, chat->builder);
    g_free(new_text);
    (void)btn;
}

void mx_connect_send_message(t_chat *chat) {
    GObject *btn_send = gtk_builder_get_object(chat->builder, "btn_send_msg");
    GObject *btn_edit = gtk_builder_get_object(chat->builder,
                                               "btn_edit_msg_apply");
    GObject *textview = gtk_builder_get_object(chat->builder, "msg_entry");

    g_signal_connect(textview, "key-press-event",
                     G_CALLBACK(mx_send_message_handle_enter), chat);
    g_signal_connect(textview, "key-release-event",
                     G_CALLBACK(mx_send_message_handle_shift), chat);
    g_signal_connect(btn_send, "clicked",
                     G_CALLBACK(mx_req_send_message), chat);
    g_signal_connect(btn_edit, "clicked",
                     G_CALLBACK(mx_req_edit_message), chat);
}
