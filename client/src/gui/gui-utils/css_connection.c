#include "client.h"

static void mx_remove_css_connect(t_chat *chat) {
    gtk_style_context_remove_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(chat->cssProv)
    );
    g_clear_object(&chat->cssProv);
    chat->cssProv = gtk_css_provider_new();
}

void mx_css_connect(char *theme, t_chat *chat) {
    if (chat->cssProv == NULL)
        chat->cssProv = gtk_css_provider_new();
    else
        mx_remove_css_connect(chat);
    gtk_css_provider_load_from_path(chat->cssProv, theme, NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(chat->cssProv),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void change_theme_icon(t_chat *chat, gchar *icon_name) {
    GObject *img = gtk_builder_get_object(chat->builder, "image19");

    gtk_image_set_from_icon_name(GTK_IMAGE(img), icon_name, GTK_ICON_SIZE_DND);
    gtk_image_set_pixel_size(GTK_IMAGE(img), 15);
}

void mx_css_connect_from_file(t_chat *chat) {
    gchar *current_theme = NULL;

    if (g_file_get_contents("../set-theme", &current_theme, NULL, NULL)
        && strcmp("light", current_theme) == 0) {
        g_file_set_contents("../set-theme", "light", -1, NULL);
        mx_css_connect(MX_LIGHT_THEME, chat);
        change_theme_icon(chat, "dark-theme");
    }
    else {
        g_file_set_contents("../set-theme", "dark", -1, NULL);
        mx_css_connect(MX_DARK_THEME, chat);
        change_theme_icon(chat, "light-theme");
    }
}
