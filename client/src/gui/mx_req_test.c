#include "client.h"

static void req_test(GtkButton *btn, t_chat *chat) {
    t_dtp *dtp = mx_upd_room_desc_request(1, "0000000000");
    printf("TEST");
    mx_send(chat->ssl, dtp);
    mx_free_request(&dtp);
    (void)btn;
}

void mx_connect_test_request(t_chat *chat) {
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_stickers"));

    g_signal_connect(btn, "clicked", G_CALLBACK(req_test), chat);
}
