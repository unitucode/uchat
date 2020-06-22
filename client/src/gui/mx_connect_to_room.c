#include "client.h"

static void req_join_to_room(t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder,
                                           MX_LISTBOX_GLOBAL_ROOMS);
    t_dtp *dtp = mx_join_room_request(groom->id);

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
}

void mx_connect_join_to_room(t_chat *chat) {
    GObject *btn = gtk_builder_get_object(chat->builder, "btn_join");

    g_signal_connect(GTK_BUTTON(btn), "clicked",
                     G_CALLBACK(req_join_to_room), chat);
}
