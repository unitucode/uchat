#include "client.h"

// static void add_message_field(gchar *msg, GtkBuilder *builder) {
//     GtkWidget *row = gtk_list_box_row_new();
//     GtkWidget *label = gtk_label_new(msg);
//     GtkWidget *box = GTK_WIDGET(gtk_builder_get_object(builder, "listbox_messages"));

//     gtk_container_add(GTK_CONTAINER(row), label);
//     gtk_widget_set_size_request(row, -1, 60);

//     gtk_list_box_insert(GTK_LIST_BOX(box), row, -1);
//     gtk_widget_show_all(GTK_WIDGET(box));

//     mx_scrlldwnd_connect("scrlldwnd_room", builder);
// }

void mx_send_message(GtkButton *btn, GtkBuilder *builder) {
    gchar *message_text = mx_get_buffer_text("buffer_message", builder);
    GtkWidget *lbl = GTK_WIDGET(gtk_builder_get_object(builder, "message"));
    gtk_label_set_text(GTK_LABEL(lbl), message_text);
    btn++;
    // add_message_field(message_text, builder);
}
