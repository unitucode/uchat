#include "client.h"

GtkBuilder *mx_init_window(int argc, char **argv) {
    GtkBuilder *builder;

    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, MX_GUI_PATH, NULL);
    gtk_builder_connect_signals(builder, builder);
    return builder;
}

int mx_start_gui(t_chat *chat) {
    // GObject *wnd_main = gtk_builder_get_object(chat->builder, "wnd_main");
    // GObject *dialog_auth = gtk_builder_get_object(chat->builder,
    //                                               "dialog_auth");

    // mx_widget_switch_visibility(NULL, GTK_WIDGET(wnd_main));
    // mx_widget_switch_visibility(NULL, GTK_WIDGET(dialog_auth));
    gtk_main();
    (void)chat;
    return 0;
}

void mx_start_main_window(t_chat *chat) {
    GObject *wnd_main = gtk_builder_get_object(chat->builder, "wnd_main");
    GObject *dialog_auth = gtk_builder_get_object(chat->builder,
                                                        "dialog_auth");

    // gtk_widget_destroy(GTK_WIDGET(dialog_auth));
    mx_widget_switch_visibility(NULL, GTK_WIDGET(wnd_main));
    mx_widget_switch_visibility(NULL, GTK_WIDGET(dialog_auth));
}
