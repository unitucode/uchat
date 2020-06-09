#include "client.h"

static void add_message_row(t_gmsg *msg, GtkBuilder *builder) {
    GtkWidget *row = mx_create_message_row(msg);
    GtkWidget *box = NULL;

    box = mx_get_groom_by_name(msg->room_name, builder)->box_messages;
    gtk_list_box_insert(GTK_LIST_BOX(box), row, -1);
    gtk_widget_show_all(GTK_WIDGET(row));
}

void mx_add_message_to_room(t_gmsg *msg, GtkBuilder *builder) {
    add_message_row(msg, builder);
}
