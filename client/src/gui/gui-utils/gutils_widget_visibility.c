#include "client.h"

gboolean mx_widget_is_visible(gchar *widget_name, GtkBuilder *builder) {
    GObject *widget = gtk_builder_get_object(builder, widget_name);

    return gtk_widget_is_visible(GTK_WIDGET(widget));
}

void mx_widget_set_visibility(GtkWidget *widget, gboolean is_visible) {
    if (is_visible)
        gtk_widget_show(widget);
    else
        gtk_widget_hide(widget);    
}

void mx_widget_set_visibility_by_name(GtkBuilder *builder,
                                      gchar *name, gboolean is_visible) {
    GtkWidget *widget = GTK_WIDGET(gtk_builder_get_object(builder, name));

    mx_widget_set_visibility(widget, is_visible);
}

void mx_widget_switch_visibility_by_name(GtkBuilder *builder, gchar *name) {
    GtkWidget *widget = GTK_WIDGET(gtk_builder_get_object(builder, name));

    mx_widget_switch_visibility(NULL, widget);
}

void mx_widget_switch_visibility(GtkWidget *usr_ctrl, GtkWidget *widget) {
    mx_widget_set_visibility(widget, !gtk_widget_is_visible(widget));
    (void)usr_ctrl;
}
