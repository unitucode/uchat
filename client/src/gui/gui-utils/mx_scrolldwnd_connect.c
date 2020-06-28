#include "client.h"

static void mx_scroll_to_end(GtkAdjustment *adj, gpointer user_data) {
    static gdouble last_value = 0;
    static gdouble last_upper = 0;
    gdouble upper = gtk_adjustment_get_upper(adj);
    gdouble value = gtk_adjustment_get_value(adj);

    if (value > (last_upper - gtk_adjustment_get_page_size(adj) - 50) || value == 0) {
        gtk_adjustment_set_value(adj, upper - gtk_adjustment_get_page_size(adj));
    }
    last_value = gtk_adjustment_get_value(adj);
    last_upper = gtk_adjustment_get_upper(adj);
    (void)user_data;
}

/*
 * Do GtkScrolledWindow autoscroll to down by name or pointer
 */
void mx_scrlldwnd_connect(gchar *name, GtkWidget *scroll,
                          GtkBuilder *builder, t_groom *room) {
    GtkWidget *scrlldwnd = NULL;
    GtkAdjustment *adj = NULL;

    if (name)
        scrlldwnd = GTK_WIDGET(gtk_builder_get_object(builder, name));
    else
        scrlldwnd = scroll;
    adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrlldwnd));
    g_signal_connect(adj, "changed", G_CALLBACK(mx_scroll_to_end), room);
}
