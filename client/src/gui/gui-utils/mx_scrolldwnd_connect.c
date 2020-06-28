#include "client.h"

static void mx_scroll_to_end(GtkAdjustment *adj, gpointer user_data) {
    // gdouble upper = gtk_adjustment_get_upper(adj);
    // gdouble curr = gtk_adjustment_get_value(adj);
    // t_groom *room = (t_groom*)user_data;
    // static gint last_uploaded = 0;
    // static gdouble last_upper = 0;
    // static gdouble last_curr = 0;

    // if (last_uploaded < room->uploaded) {
    //     gtk_adjustment_set_value(adj, 0);
    // }
    // last_uploaded = room->uploaded;
    // last_upper = upper;
    // last_curr = curr + gtk_adjustment_get_page_size(adj);
    (void)adj;
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
