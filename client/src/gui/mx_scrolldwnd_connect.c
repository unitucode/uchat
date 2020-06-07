#include "client.h"

static void mx_scroll_to_end(GtkAdjustment *adj) {
    static gdouble i = 0;
    gdouble x = gtk_adjustment_get_upper(adj);

    if (i < x)
        gtk_adjustment_set_value(adj, x);
    i = x;
}

void mx_scrlldwnd_connect(char *wnd_name, GtkBuilder *builder) {
    GtkWidget *scroll = GTK_WIDGET(gtk_builder_get_object(builder, wnd_name));
    GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scroll));

    g_signal_connect(adj, "changed", G_CALLBACK(mx_scroll_to_end), NULL);
}
