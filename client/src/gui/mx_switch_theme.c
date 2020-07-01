#include "client.h"

static void set_light_theme(t_chat *chat) {
    g_file_set_contents(MX_THEME_FILE, "light", -1, NULL);
    mx_css_connect(MX_LIGHT_THEME, chat);
    change_theme_icon(chat, "dark-theme");
}

static void enable_opposite_theme(gchar *current_name, t_chat *chat) {
    if (!g_strcmp0("dark", current_name)) {
        g_file_set_contents(MX_THEME_FILE, "light", -1, NULL);
        mx_css_connect(MX_LIGHT_THEME, chat);
        change_theme_icon(chat, "dark-theme");
    }
    else {
        g_file_set_contents(MX_THEME_FILE, "dark", -1, NULL);
        mx_css_connect(MX_DARK_THEME, chat);
        change_theme_icon(chat, "light-theme");
    }
}

void mx_switch_theme(GtkWidget *widget, t_chat *chat) {
    gchar *current_theme = NULL;

    if (g_file_get_contents(MX_THEME_FILE, &current_theme, NULL, NULL))
        enable_opposite_theme(current_theme, chat);
    else
        set_light_theme(chat);
    if (current_theme)
        g_free(current_theme);
    (void)widget;
}

void mx_connect_theme_switcher(t_chat *chat) {
    GObject *btn = gtk_builder_get_object(chat->builder, "btn_change_theme");

    g_signal_connect(btn, "clicked", G_CALLBACK(mx_switch_theme), chat);
}
