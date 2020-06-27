#include "client.h"

static void mx_scroll_to_end(GtkAdjustment *adj) {
    static gdouble last_value = 0;
    static gdouble last_upper = 0;

    gdouble upper = gtk_adjustment_get_upper(adj);
    gdouble value = gtk_adjustment_get_value(adj);
    // gdouble lower = gtk_adjustment_get_lower(adj);

    if (last_value < value) {
        printf("\nset up value one\n");
        gtk_adjustment_set_value(adj, value);
    }
    else if (last_upper < upper) {
        g_print("value          == %f\n", gtk_adjustment_get_value(adj));
        g_print("lower          == %f\n", gtk_adjustment_get_lower(adj));
        g_print("upper          == %f\n", gtk_adjustment_get_upper(adj));
        g_print("page_size      == %f\n", gtk_adjustment_get_page_size(adj));
        value = (upper - gtk_adjustment_get_page_size(adj));
        g_print("\nset up value -> %f\n", value);
        gtk_adjustment_set_value(adj, value);
    }
    else if (value < last_value) {
        if(last_upper)
            upper = last_upper;
        gtk_adjustment_set_upper(adj, upper);
        value = (upper - gtk_adjustment_get_page_size(adj));
        g_print("\nset up value -> %f\n", value);
        gtk_adjustment_set_value(adj, value);
    }
    g_print("\nvalue          == %f\n", gtk_adjustment_get_value(adj));
    g_print("lower          == %f\n", gtk_adjustment_get_lower(adj));
    g_print("upper          == %f\n", gtk_adjustment_get_upper(adj));
    g_print("page_size      == %f\n", gtk_adjustment_get_page_size(adj));
    g_print("last_value     == %f\n", last_value);
    g_print("lasr_upper     == %f\n\n", last_upper);
    last_value = gtk_adjustment_get_value(adj);
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
