#include "client.h"

GtkBuilder *mx_init_window(gint argc, char **argv) {
    GtkBuilder *builder;

    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, MX_GUI_PATH, NULL) == 0)
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_ERROR,
                  "Gui.glade is missing(xml file).");
    gtk_builder_connect_signals(builder, builder);
    return builder;
}

static void change_icontheme_paths(GtkBuilder *builder) {
    GObject *desc = gtk_builder_get_object(builder, "buffer_message");
    const gchar *path[] = {"../src/gui/resources",
                           "../src/gui/resources/stickers",
                           "../src/gui/resources/Adwaita"};

    gtk_icon_theme_set_search_path(gtk_icon_theme_get_default(), path, 3);
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(desc), "Enter your message", -1);
}

gint mx_start_gui(t_chat *chat) {
    change_icontheme_paths(chat->builder);
    gtk_main();
    return 0;
}

void mx_start_main_window(t_chat *chat) {
    GObject *wnd_main = gtk_builder_get_object(chat->builder, "wnd_main");
    GObject *dialog_auth = gtk_builder_get_object(chat->builder,
                                                  "dialog_auth");

    mx_widget_switch_visibility(NULL, GTK_WIDGET(dialog_auth));
    mx_widget_switch_visibility(NULL, GTK_WIDGET(wnd_main));
    mx_reset_auth(NULL, NULL, -1, chat->builder);
}
