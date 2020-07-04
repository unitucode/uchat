#include "client.h"

/*
    void mx_widget_set_class() - Adds a class to the widget.
        > GtkWidget *widget - The widget to which you want to add a class;
        > gchar *class - The name of the class you want to add.
*/
void mx_widget_set_class(GtkWidget *widget, gchar *class) {
    GtkStyleContext *context = gtk_widget_get_style_context(widget);

    gtk_style_context_add_class(context, class);
}

/*
    void mx_widget_set_class() - Removes a class from a widget.
        > GtkWidget *widget - The widget you want to remove the class from;
        > gchar *class - The name of the class you want to remove.
*/
void mx_widget_remove_class(GtkWidget *widget, gchar *class) {
    GtkStyleContext *context = gtk_widget_get_style_context(widget);

    gtk_style_context_remove_class(context, class);
}
