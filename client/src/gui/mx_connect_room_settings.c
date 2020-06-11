#include "client.h"

void req_room_sett(GtkButton *btn, t_chat *chat) {
    (void)btn;
}

void mx_connect_room_settings(t_chat *chat) {
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_room_sett_apply"));

    g_signal_connect(btn, "clicked", G_CALLBACK(req_room_sett), chat);
}
