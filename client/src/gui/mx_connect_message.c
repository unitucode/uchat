#include "client.h"

static void req_send_message(GtkButton *btn, t_chat *chat) {
    gchar *message_text = mx_get_buffer_text("buffer_message", chat->builder);
    t_groom *room = mx_get_selected_groom(chat->builder,  MX_LOCAL_ROOMS);
    t_dtp *dtp = NULL;

    if (room && !chat->msg_placeholder) {
        dtp = mx_msg_request(message_text, room->id);
        mx_send(chat->out, dtp);
        mx_free_request(&dtp);
        mx_clear_buffer_text("buffer_message", chat->builder);
    }
    (void)btn;
}

static void req_edit_message(GtkButton *btn, t_chat *chat) {
    t_gmsg *gmsg = mx_get_selected_gmsg(chat->builder);
    char *new_text = mx_get_buffer_text("buffer_message", chat->builder);
    t_dtp *dtp = NULL;

    if (strcmp(gmsg->msg, new_text)) {
        dtp = mx_edit_msg_request(new_text, gmsg->room_id, gmsg->message_id);
        mx_send(chat->out, dtp);
        mx_free_request(&dtp);
    }
    else
        mx_switch_room_header(chat->builder, MX_MSG_CTRL);
    mx_clear_buffer_text("buffer_message", chat->builder);
    mx_hide_msg_editing(NULL, chat->builder);
    (void)btn;
}

void mx_connect_send_message(t_chat *chat) {
    GObject *btn_send = gtk_builder_get_object(chat->builder, "btn_send_msg");
    GObject *btn_edit = gtk_builder_get_object(chat->builder,
                                               "btn_edit_msg_apply");

    g_signal_connect(btn_send, "clicked", G_CALLBACK(req_send_message), chat);
    g_signal_connect(btn_edit, "clicked", G_CALLBACK(req_edit_message), chat);
}
