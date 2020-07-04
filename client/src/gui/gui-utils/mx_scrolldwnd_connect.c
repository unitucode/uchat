#include "client.h"

/*
 * Show "Go Down" butoon when user go up
 */
static void mx_show_go_down(GtkAdjustment *adj, GtkBuilder *builder) {
    GObject *go_down = gtk_builder_get_object(builder, "btn_go_down");
    gdouble upper = gtk_adjustment_get_upper(adj);
    gdouble value = gtk_adjustment_get_value(adj);

    if (value < (upper - gtk_adjustment_get_page_size(adj) - 50))
        mx_widget_set_visibility(GTK_WIDGET(go_down), TRUE);
    else
        mx_widget_set_visibility(GTK_WIDGET(go_down), FALSE);
}

/*
 * Do GtkScrolledWindow autoscroll to down by name or pointer
 */
static void mx_scroll_to_end(GtkAdjustment *adj, gpointer user_data) {
    static GtkAdjustment *last_adj = 0;
    static gdouble last_upper = 0;
    gdouble upper = gtk_adjustment_get_upper(adj);
    gdouble value = gtk_adjustment_get_value(adj);

    if (last_adj != adj)
        value = 0;
    if (upper < gtk_adjustment_get_page_size(adj)) {}
    else if (value > (last_upper - gtk_adjustment_get_page_size(adj) - 50) ||
            value == 0) {
        gtk_adjustment_set_value(adj,
                                 upper - gtk_adjustment_get_page_size(adj));
    }
    last_upper = gtk_adjustment_get_upper(adj);
    last_adj = adj;
    (void)user_data;
}

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
    g_signal_connect(adj, "changed", G_CALLBACK(mx_show_go_down), builder);
    g_signal_connect(adj, "value-changed", G_CALLBACK(mx_show_go_down),
                     builder);
}
