#include "client.h"

gboolean shift_hold;

void mx_send_message_handle_enter(GtkWidget *textview,
                                  GdkEvent *event, t_chat *chat) {
    if (event->key.keyval == (gint)65505)
        shift_hold = TRUE;
    sleep(0);
    if (event->key.keyval == (gint)65293 && !shift_hold) {
        mx_req_send_message(NULL, chat);
        mx_clear_buffer_text("buffer_message", chat->builder);
    }
    (void)textview;
    (void)chat;
}

void mx_send_message_handle_shift(GtkWidget *textview,
                                  GdkEvent *event, GtkBuilder *builder) {
    if (event->key.keyval == (gint)65505)
        shift_hold = FALSE;
    (void)textview;
    (void)builder;
}

