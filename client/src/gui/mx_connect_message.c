#include "client.h"

static void req_send_message(GtkButton *btn, t_chat *chat) {
    gchar *message_text = mx_get_buffer_text("buffer_message", chat->builder);
    t_groom *room = mx_get_selected_groom(chat->builder);
    t_dtp *dtp = NULL;

    if (room) {
        dtp = mx_msg_request(message_text, room->id);
        mx_send(chat->out, dtp);
        mx_free_request(&dtp);
        mx_clear_buffer_text("buffer_message", chat->builder);
    }
    (void)btn;
}

void mx_connect_send_message(t_chat *chat) {
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_send"));

    g_signal_connect(btn, "clicked", G_CALLBACK(req_send_message), chat);
}
