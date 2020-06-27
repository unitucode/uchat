#include "client.h"

static void mx_scroll_to_end(GtkAdjustment *adj, gpointer user_data) {
    // static gdouble last_value = 0;
    // static gdouble last_upper = 0;

    // gdouble upper = gtk_adjustment_get_upper(adj);
    // gdouble value = gtk_adjustment_get_value(adj);
    // gdouble lower = gtk_adjustment_get_lower(adj);

    // if (last_value < value)
    //     gtk_adjustment_set_value(adj, value);
    // else if (last_upper < upper && lower == 0) {
    //     g_print("\nset up value -> %f\n", value);
    //     g_print("value          == %f\n", gtk_adjustment_get_value(adj));
    //     g_print("lower          == %f\n", gtk_adjustment_get_lower(adj));
    //     g_print("upper          == %f\n", gtk_adjustment_get_upper(adj));
    //     g_print("step increment == %f\n", gtk_adjustment_get_step_increment(adj));
    //     g_print("page increment == %f\n", gtk_adjustment_get_page_increment(adj));
    //     g_print("page size      == %f\n\n", gtk_adjustment_get_page_size(adj));
    //     gtk_adjustment_set_upper(adj, last_upper);
    //     value = (upper - gtk_adjustment_get_page_size(adj));
    //     gtk_adjustment_set_value(adj, value);
    // }
    // g_print("\nvalue          == %f\n", gtk_adjustment_get_value(adj));
    // g_print("lower          == %f\n", gtk_adjustment_get_lower(adj));
    // g_print("upper          == %f\n", gtk_adjustment_get_upper(adj));
    // g_print("step increment == %f\n", gtk_adjustment_get_step_increment(adj));
    // g_print("page increment == %f\n", gtk_adjustment_get_page_increment(adj));
    // g_print("page size      == %f\n", gtk_adjustment_get_page_size(adj));
    // g_print("last_value     == %f\n", last_value);
    // g_print("lasr_upper     == %f\n\n", last_upper);
    // last_value = gtk_adjustment_get_value(adj);
    // last_upper = upper;
    (void)adj;
    (void)user_data;
}

/*
 * Do GtkScrolledWindow autoscroll to down by name or pointer
 */
void mx_scrlldwnd_connect(gchar *name, GtkWidget *scroll,
                          GtkBuilder *builder, t_chat *chat) {
    GtkWidget *scrlldwnd = NULL;
    GtkAdjustment *adj = NULL;

    if (name)
        scrlldwnd = GTK_WIDGET(gtk_builder_get_object(builder, name));
    else
        scrlldwnd = scroll;
    adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrlldwnd));
    g_signal_connect(adj, "changed", G_CALLBACK(mx_scroll_to_end), chat);
}
