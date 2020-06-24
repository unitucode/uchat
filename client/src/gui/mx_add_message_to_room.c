#include "client.h"

static void add_message_row(t_gmsg *msg, t_chat *chat) {
    GtkWidget *row = gtk_list_box_row_new();
    GtkWidget *event = mx_create_message_row(chat, msg);
    t_groom *groom = mx_get_groom_by_id(msg->room_id, chat->builder);
    GtkListBox *box = groom->box_messages;
    t_signal_data *data = NULL;

    gtk_widget_set_can_focus(row, FALSE);
    data = mx_create_sigdata(chat, NULL, GTK_LIST_BOX_ROW(row));

    msg->row_msg = GTK_LIST_BOX_ROW(row);
    g_object_ref(row);

    gtk_container_add(GTK_CONTAINER(row), event);
    g_signal_connect(event, "button_release_event",
                     G_CALLBACK(mx_select_msg), data);
    groom->is_updated = true;
    gtk_list_box_insert(box, row, -1);
    gtk_list_box_row_changed(groom->row_room);
    groom->is_updated = false;
    groom->is_watched = false;
    // mx_widget_set_class(GTK_WIDGET(box), "room-unwatched");
    gtk_widget_show_all(GTK_WIDGET(box));
    g_object_set_data_full(G_OBJECT(row), "gmsg", msg,
                           (GDestroyNotify)mx_delete_gmsg);
    g_object_set_data_full(G_OBJECT(event), "sigdata", data,
                           (GDestroyNotify)mx_free_sigdata);
}

void mx_add_message_to_room(t_gmsg *msg, t_chat *chat) {
    add_message_row(msg, chat);
}
