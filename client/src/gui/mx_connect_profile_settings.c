#include "client.h"

static void req_get_member_info(GObject *popup, t_chat *chat) {
    t_dtp *dtp = mx_member_info_request((int)g_object_get_data(popup,
                                                               "member_id"));

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
}

static void req_logout(GtkButton *btn, t_chat *chat) {
    t_dtp *logout = mx_log_out_request(chat->auth_token);

    mx_send(chat->out, logout);
    mx_free_request(&logout);
    (void)btn;
}

void mx_connect_profile_settings(t_chat *chat) {
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_logout"));
    GObject *popup = gtk_builder_get_object(chat->builder, "popup_user_info");

    g_signal_connect(btn, "clicked", G_CALLBACK(req_logout), chat);
    g_signal_connect(popup, "show", G_CALLBACK(req_get_member_info), chat);
}
