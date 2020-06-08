#include "client.h"

static void add_message_row(t_gmsg *msg, GtkBuilder *builder) {
    GtkWidget *row = mx_create_message_row(msg);
    GtkWidget *box = mx_get_selected_groom(builder)->box_messages;

    gtk_list_box_insert(GTK_LIST_BOX(box), row, -1);
    gtk_widget_show_all(GTK_WIDGET(box));
}

void mx_add_message_to_room(t_gmsg *msg, GtkBuilder *builder) {
    mx_clear_buffer_text("buffer_message", builder);
    add_message_row(msg, builder);
}
