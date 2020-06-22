#include "client.h"

static void req_test(GtkButton *btn, t_chat *chat) {
    // mx_upload_file("/Users/okhomin/Desktop/ucode/uchat/uchat/client/src/gui/resources/edit.png", chat);
    // t_dtp *request = mx_search_rooms_request("1");
    // t_dtp *request = mx_join_room_request(2);
    // t_dtp *request = mx_get_members_request(2);
    // t_dtp *request = mx_member_info_request(2);
    // t_dtp *request = mx_ban_member_request(2, 3);
    t_dtp *request = mx_sticker_request("hello.png", 1);
    mx_send(chat->out, request);
    mx_free_request(&request);
    (void)chat;
    (void)btn;
}

void mx_connect_test_request(t_chat *chat) {
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_attachment"));

    g_signal_connect(btn, "clicked", G_CALLBACK(req_test), chat);
}
