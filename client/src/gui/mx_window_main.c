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

    // GdkPixbuf *hilvl = gdk_pixbuf_new_from_file("../src/gui/resources/attach(1).png", NULL);
    
    // GdkPixbuf *new = gdk_pixbuf_scale_simple(hilvl, 50, 50, GDK_INTERP_HYPER);
    
    // GtkWidget *img = gtk_image_new_from_pixbuf(new);
    // GObject *button = gtk_builder_get_object(chat->builder, "btn_stickers");
    // gtk_button_set_image(GTK_BUTTON(button), img);

    // GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("../src/gui/resources/attach(1).png", NULL);
    // int width, height;

    // gdk_pixbuf_get_file_info("../src/gui/resources/attach(1).png", &width, &height);
    // gtk_icon_theme_add_builtin_icon("link_icon", width, pixbuf);
    // g_object_unref (G_OBJECT (pixbuf)); 

    // GObject *button = gtk_builder_get_object(chat->builder, "btn_stickers");
    // GtkWidget *img = gtk_image_new_from_icon_name("link_icon", 18);
    // gtk_button_set_image (GTK_BUTTON(button), img);
    const gchar *path[] = {"../src/gui/resources"};
    gtk_icon_theme_set_search_path(gtk_icon_theme_get_default(), path, 1);
    GObject *button = gtk_builder_get_object(chat->builder, "btn_stickers");
    GtkWidget *img = gtk_image_new_from_icon_name("attach(1)", GTK_ICON_SIZE_LARGE_TOOLBAR);
    gtk_button_set_image (GTK_BUTTON(button), img);

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
