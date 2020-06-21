#include "client.h"

void mx_widget_set_class(GtkWidget *widget, gchar *class) {
    GtkStyleContext *context = gtk_widget_get_style_context(widget);

    gtk_style_context_add_class(context, class);
}
