#include "client.h"

static void req_test(GtkButton *btn, t_chat *chat) {
    // mx_upload_file("/Users/okhomin/Desktop/ucode/uchat/uchat/client/src/gui/resources/add-room.png", 1, chat);
    mx_download_file(1, 2, chat);
    // t_groom *room = mx_get_groom_by_id(1, chat->builder);
    // mx_widget_set_class(GTK_WIDGET(room->label_name), "has-messages");
    // t_dtp *request = mx_search_rooms_request("1");
    // t_dtp *request = mx_join_room_request(1);
    // t_dtp *request = mx_get_members_request(2);
    // t_dtp *request = mx_member_info_request(2);
    // t_dtp *request = mx_ban_member_request(2, 3);
    // t_dtp *request = mx_sticker_request("sticker_wind.png", 1);
    // t_dtp *request = mx_del_hist_request(1);
    // t_dtp *request = mx_old_msgs_request(1592992466258, 1);
    // mx_send(chat->out, request);
    // mx_free_request(&request);
    (void)chat;
    (void)btn;
}

void mx_connect_test_request(t_chat *chat) {
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_attachment"));

    g_signal_connect(btn, "clicked", G_CALLBACK(req_test), chat);
}
