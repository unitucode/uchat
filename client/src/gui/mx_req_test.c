#include "client.h"

static void req_test(GtkButton *btn, t_chat *chat) {
    mx_upload_file("../Makefile", chat);
    (void)chat;
    (void)btn;
}

void mx_connect_test_request(t_chat *chat) {
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_stickers"));

    g_signal_connect(btn, "clicked", G_CALLBACK(req_test), chat);
}
