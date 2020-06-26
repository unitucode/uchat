#include "client.h"

static void mx_scroll_to_end(GtkAdjustment *adj) {
    static gdouble last_curr = 0;
    static gdouble last_upper = 0;
    gdouble upper = gtk_adjustment_get_upper(adj);
    gdouble lower = gtk_adjustment_get_page_size(adj);
    gdouble curr = gtk_adjustment_get_value(adj) + lower;

    g_print("\n\nupper = %f\n", upper);
    g_print("last_upper = %f\n", last_upper);
    g_print("last_curr = %f\n", last_curr);
    g_print("curr = %f\n", curr);
    if (last_curr < curr)
        gtk_adjustment_set_value(adj, last_curr);
    else if (curr == last_curr && curr == last_upper) {
        g_print("set to %f\n", upper);
        gtk_adjustment_set_value(adj, upper);
    }
    last_curr = curr;
    last_upper = upper;
}

/*
 * Do GtkScrolledWindow autoscroll to down by name or pointer
 */
void mx_scrlldwnd_connect(gchar *name,
                          GtkWidget *scroll, GtkBuilder *builder) {
    GtkWidget *scrlldwnd = NULL;
    GtkAdjustment *adj = NULL;

    if (name)
        scrlldwnd = GTK_WIDGET(gtk_builder_get_object(builder, name));
    else
        scrlldwnd = scroll;
    adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrlldwnd));
    g_signal_connect(adj, "changed", G_CALLBACK(mx_scroll_to_end), NULL);
}
