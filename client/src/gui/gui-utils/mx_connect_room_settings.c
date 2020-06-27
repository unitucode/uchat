#include "client.h"

void mx_connect_room_settings(t_chat *chat) {
    GObject *btn_sett = gtk_builder_get_object(chat->builder,
                                               "btn_show_room_sett");
    GObject *btn_apply = gtk_builder_get_object(chat->builder,
                                                "btn_roomsett_apply");
    GObject *btn_delete = gtk_builder_get_object(chat->builder,
                                                 "btn_roomsett_delete");
    GObject *btn_clear = gtk_builder_get_object(chat->builder,
                                                "btn_clear_history");

    g_signal_connect(btn_sett, "clicked", G_CALLBACK(mx_set_room_sett), chat);
    g_signal_connect(btn_apply, "clicked", G_CALLBACK(mx_req_room_sett), chat);
    g_signal_connect(btn_clear, "clicked", G_CALLBACK(mx_req_room_clear), chat);
    g_signal_connect(btn_delete, "clicked", G_CALLBACK(mx_req_room_del), chat);
}
