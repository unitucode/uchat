#include "client.h"

static void mx_scroll_to_end(GtkAdjustment *adj, gpointer user_data) {
    static gdouble last_value = 0;
    static gdouble last_upper = 0;
    t_groom *room = (t_groom*)user_data;
    gdouble upper = gtk_adjustment_get_upper(adj);
    gdouble upper_f = upper - last_upper;

    gdouble value = last_value + upper_f;
    gtk_adjustment_set_value(adj, value);
    if (room->uploaded == MX_BUF_MSGS) {
        if (last_upper) {
            upper = last_upper;
            gtk_adjustment_set_upper(adj, upper);
        }
    }
    else if (room->uploaded > MX_BUF_MSGS) {}
    value = last_value + upper_f;
    gtk_adjustment_set_value(adj, value);

    g_print("\nvalue    == %f\n", gtk_adjustment_get_value(adj));
    g_print("last_value == %f\n\n", last_value);
    g_print("\nlower      == %f\n", gtk_adjustment_get_lower(adj));
    g_print("upper      == %f\n", gtk_adjustment_get_upper(adj));
    g_print("last_upper == %f\n", last_upper);
    g_print("page_size  == %f\n\n", gtk_adjustment_get_page_size(adj));
    last_value = gtk_adjustment_get_value(adj);
    last_upper = gtk_adjustment_get_upper(adj);
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
