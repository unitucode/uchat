#include "client.h"

static void req_send_message(GtkButton *btn, t_chat *chat) {
    // gchar *message_text = mx_get_buffer_text("buffer_message", chat->builder);

    // mx_clear_buffer_text("buffer_message", chat->builder);
    (void)btn;
    (void)chat;
}

void mx_connect_send_message(t_chat *chat) {
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_send"));

    g_signal_connect(btn, "clicked", G_CALLBACK(req_send_message), chat);
}
