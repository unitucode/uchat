#include "client.h"

static void add_message_row(t_gmsg *msg, GtkBuilder *builder) {
    GtkWidget *row = mx_create_message_row(msg);
    t_groom *room = mx_get_groom_by_name(msg->room_name, builder);
    GtkWidget *box = room->box_messages;

    room->is_updated = true;
    gtk_list_box_insert(GTK_LIST_BOX(box), row, -1);
    gtk_list_box_row_changed(room->row_room);
    room->is_updated = false;
    gtk_widget_show_all(GTK_WIDGET(box));
}

void mx_add_message_to_room(t_gmsg *msg, GtkBuilder *builder) {
    mx_clear_buffer_text("buffer_message", builder);
    add_message_row(msg, builder);
}
