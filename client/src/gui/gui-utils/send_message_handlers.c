#include "client.h"

gboolean shift_hold;

void mx_send_message_handle_enter(GtkTextView *textview,
                                  GdkEvent *event, t_chat *chat) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);

    if (event->key.keyval == (gint)65505)
        shift_hold = TRUE;
    g_usleep(0);
    if (event->key.keyval == (gint)65293) {
        if (shift_hold)
            gtk_text_buffer_insert_at_cursor(buffer, "\n", -1);
        else {
            mx_req_send_message(NULL, chat);
            mx_clear_buffer_text("buffer_message", chat->builder);
        }
    }
}

void mx_send_message_handle_shift(GtkWidget *textview,
                                  GdkEvent *event, GtkBuilder *builder) {
    if (event->key.keyval == (gint)65505)
        shift_hold = FALSE;
    (void)textview;
    (void)builder;
}

