#include "client.h"

void mx_req_addroom(GtkButton *btn, t_chat *chat) {
    char *room_name = mx_get_buffer_text("buffer_roomname", chat->builder);
    t_dtp *dtp = mx_new_room_request(room_name, 0, NULL);

    mx_send(chat->ssl, dtp);
    mx_free_request_struct(&dtp);
    (void)btn;
}

static void connect_addroom(t_chat *chat) {
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_addroom_apply"));

    g_signal_connect(btn, "clicked", G_CALLBACK(mx_req_addroom), chat);
}

void mx_init_gui(t_chat *chat) {
    connect_addroom(chat);
}
