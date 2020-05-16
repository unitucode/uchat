#include "client.h"

static void scroll_to_end(GtkAdjustment *adj) {
    static gdouble i = 0;
    gdouble x = gtk_adjustment_get_upper(adj);

    if (i < x)
        gtk_adjustment_set_value(adj, x);
    i = x;
}

static void create_row_room(GtkBuilder *builder) {
    GtkWidget *row = gtk_list_box_row_new();
    GtkWidget *label = gtk_label_new("New Room");
    GtkWidget *box = GTK_WIDGET(gtk_builder_get_object(builder, "listbox_rooms"));

    gtk_widget_set_name(row, "row");
    gtk_container_add(GTK_CONTAINER(row), label);
    gtk_widget_set_size_request(row, -1, 80);

    gtk_list_box_insert(GTK_LIST_BOX(box), row, -1);
    gtk_widget_show_all(GTK_WIDGET(box));

    GtkWidget *scroll = GTK_WIDGET(gtk_builder_get_object(builder, "scrlldwnd_rooms"));
    GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scroll));
    g_signal_connect (adj, "changed", G_CALLBACK(scroll_to_end), NULL);
}

void mx_add_room(GtkButton *btn, GtkBuilder *builder) {
    create_row_room(builder);
}
