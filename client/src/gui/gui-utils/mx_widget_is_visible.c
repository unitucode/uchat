#include "client.h"

bool mx_widget_is_visible(char *widget_name, GtkBuilder *builder) {
    GObject *widget = gtk_builder_get_object(builder, widget_name);

    return gtk_widget_is_visible(GTK_WIDGET(widget));
}
