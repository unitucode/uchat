#include "client.h"

int mx_window_main(int argc, char **argv) {
    GObject *wnd_main;
    GtkBuilder *builder;

    gtk_init (&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, MX_GUI_PATH, NULL);
    gtk_builder_connect_signals(builder, builder);
    g_object_ref(builder);
    g_object_unref(builder);
    wnd_main = gtk_builder_get_object(builder, "wnd_main");
    gtk_widget_show_all(GTK_WIDGET(wnd_main));
    gtk_main();
    return 0;
}

int main(int argc, char **argv) {
    mx_window_main(argc, argv);
    return 0;
}
