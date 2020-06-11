#include "client.h"

static void req_room_sett(GtkButton *btn, t_chat *chat) {
    GObject *label_name = gtk_builder_get_object(chat->builder,
                                                 "label_prefs_roomname");
    gchar *name = mx_get_buffer_text("buffer_roomname", chat->builder);
    puts(name);
    gtk_label_set_text(GTK_LABEL(label_name), name);
    (void)btn;
}

void mx_connect_room_settings(t_chat *chat) {
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_room_sett_apply"));

    g_signal_connect(btn, "clicked", G_CALLBACK(req_room_sett), chat);
}
