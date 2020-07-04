#include "client.h"

void mx_connect_room_settings(t_chat *chat) {
    GObject *sett = gtk_builder_get_object(chat->builder,
                                           "btn_show_room_sett");
    GObject *apply = gtk_builder_get_object(chat->builder,
                                            "btn_roomsett_apply");
    GObject *delete = gtk_builder_get_object(chat->builder,
                                             "btn_roomsett_delete");
    GObject *clear = gtk_builder_get_object(chat->builder,
                                            "btn_clear_history");

    g_signal_connect(sett, "clicked", G_CALLBACK(mx_set_room_sett), chat);
    g_signal_connect(apply, "clicked", G_CALLBACK(mx_req_room_sett), chat);
    g_signal_connect(clear, "clicked", G_CALLBACK(mx_req_room_clear), chat);
    g_signal_connect(delete, "clicked", G_CALLBACK(mx_req_room_del), chat);
}
