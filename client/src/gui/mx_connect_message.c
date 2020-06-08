#include "client.h"

static char *mx_get_selected_room_name(GtkBuilder *builder) {
    GtkListBox *box = GTK_LIST_BOX(gtk_builder_get_object(builder,
                                                          "listbox_rooms"));
    GtkContainer *row = GTK_CONTAINER(gtk_list_box_get_selected_row(box));
    GList *list_row = gtk_container_get_children(row);
    GList *list_event = gtk_container_get_children(GTK_CONTAINER(list_row->data));
    GtkLabel *label = GTK_LABEL(list_event->data);

    return (char*)gtk_label_get_text(label);
}

static void req_send_message(GtkButton *btn, t_chat *chat) {
    gchar *message_text = mx_get_buffer_text("buffer_message", chat->builder);
    char *room_name = mx_get_selected_room_name(chat->builder);
    t_dtp *dtp = mx_msg_request(message_text, room_name);

    mx_send(chat->ssl, dtp);
    mx_free_request(&dtp);
    mx_clear_buffer_text("buffer_message", chat->builder);
    (void)btn;
}

void mx_connect_send_message(t_chat *chat) {
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_send"));

    g_signal_connect(btn, "clicked", G_CALLBACK(req_send_message), chat);
}
