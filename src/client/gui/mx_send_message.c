#include "client.h"

void scroll_to_end(GtkAdjustment *adj) {
    static gdouble i = 0;
    gdouble x = gtk_adjustment_get_upper(adj);

    if (i < x)
        gtk_adjustment_set_value(adj, x);
    i = x;
}

static void add_message_field(gchar *msg, GtkBuilder *builder) {
    GtkWidget *row = gtk_list_box_row_new();
    GtkWidget *label = gtk_label_new(msg);
    GtkWidget *box = GTK_WIDGET(gtk_builder_get_object(builder, "listbox_messages"));

    gtk_container_add(GTK_CONTAINER(row), label);
    gtk_widget_set_size_request(row, -1, 60);

    gtk_list_box_insert(GTK_LIST_BOX(box), row, -1);
    gtk_widget_show_all(GTK_WIDGET(box));

    GtkWidget *scroll = GTK_WIDGET(gtk_builder_get_object(builder, "scrlldwnd_room"));
    GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scroll));
    g_signal_connect (adj, "changed", G_CALLBACK(scroll_to_end), NULL);
}

static gchar *get_message_text(GtkBuilder *builder) {
    GtkTextBuffer *buffer = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "buffer_messager"));
    GtkTextIter start;
    GtkTextIter end;

    gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(buffer), &start);
    gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(buffer), &end);
    return gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer), &start, &end, FALSE);
}

void mx_send_message(GtkButton *btn, GtkBuilder *builder) {
    gchar *message_text = get_message_text(builder);

    add_message_field(message_text, builder);
}
