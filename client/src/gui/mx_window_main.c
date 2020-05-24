#include "client.h"
// #include <gtk/gtk.h>

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
    GObject *wnd_main;

    wnd_main = gtk_builder_get_object(chat->builder, "wnd_main");
    printf("chdir = %d\n", chdir(MX_GUI_PATH));
    gtk_widget_show_all(GTK_WIDGET(wnd_main));
    gtk_main();
    return 0;
}

// int main(int argc, char **argv) {
//     mx_window_main(argc, argv);
//     system("leaks -q gui");
//     return 0;
// }
