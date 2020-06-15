#include "client.h"

static void req_logout(GtkButton *btn, t_chat *chat) {
    t_dtp *logout = mx_log_out_request(chat->auth_token);

    mx_send_request(chat, logout);
    mx_free_request(&logout);
    (void)btn;
}

void mx_connect_profile_settings(t_chat *chat) {
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_logout"));

    g_signal_connect(btn, "clicked", G_CALLBACK(req_logout), chat);
}
