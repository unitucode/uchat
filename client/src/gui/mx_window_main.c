#include "client.h"

GtkBuilder *mx_init_window(int argc, char **argv) {
    GtkBuilder *builder;

    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, MX_GUI_PATH, NULL);
    gtk_builder_connect_signals(builder, builder);
    g_object_ref(builder);
    g_object_unref(builder);
    return builder;
}

int mx_start_window(t_chat *chat) {
    // GObject *wnd_main = gtk_builder_get_object(chat->builder, "wnd_main");
    GObject *wnd_authorization = gtk_builder_get_object(chat->builder,
                                                        "wnd_authorization");

    // gtk_widget_show_all(GTK_WIDGET(wnd_main));
    gtk_widget_show_all(GTK_WIDGET(wnd_authorization));
    gtk_main();
    return 0;
}
