#include "client.h"

GtkBuilder *mx_init_window(int argc, char **argv) {
    GtkBuilder *builder;

    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, MX_GUI_PATH, NULL);
    gtk_builder_connect_signals(builder, builder);
    mx_css_connect();
    return builder;
}

int mx_start_gui(t_chat *chat) {
    // GdkPixbuf *svg = gdk_pixbuf_new_from_file("../src/gui/resources/web-browser.tiff", NULL);
    // GtkWidget *img = gtk_image_new_from_pixbuf(svg);
    // GObject *button = gtk_builder_get_object(chat->builder, "btn_show_roomlist");
    // gtk_button_set_image(GTK_BUTTON(button), img);
    
    GtkIconTheme *icon_theme = gtk_icon_theme_get_default();;
    gtk_icon_theme_add_resource_path(icon_theme, "../src/gui/resources");

    gtk_main();

    (void)chat;
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
