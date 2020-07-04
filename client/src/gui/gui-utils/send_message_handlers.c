#include "client.h"

void mx_send_message_handle_enter(GtkTextView *textview,
                                  GdkEvent *event, t_chat *chat) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);

    if (event->key.keyval == MX_KEY_SHIFT)
        chat->shift_hold = TRUE;
    g_usleep(0);
    if (event->key.keyval == MX_KEY_ENTER) {
        if (chat->shift_hold)
            gtk_text_buffer_insert_at_cursor(buffer, "\n", -1);
        else if (!mx_widget_is_visible("box_editing_msg", chat->builder)){
            mx_req_send_message(NULL, chat);
            mx_clear_buffer_text("buffer_message", chat->builder);
        }
        else
            mx_req_edit_message(NULL, chat);
    }
}

void mx_send_message_handle_shift(GtkWidget *textview,
                                  GdkEvent *event, t_chat *chat) {
    if (event->key.keyval == MX_KEY_SHIFT)
        chat->shift_hold = FALSE;
    (void)textview;
}

