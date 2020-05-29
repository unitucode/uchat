#include "client.h"

void mx_req_addroom(GtkButton *btn, t_chat *chat) {
    char *room_name = mx_get_buffer_text("buffer_roomname", chat->builder);
    char *room_pass = mx_get_buffer_text("buffer_roompass", chat->builder);
    bool is_private = false;
    t_dtp *dtp = NULL;

    is_private = strcmp(room_pass, "");
    dtp = mx_new_room_request(room_name, is_private, room_pass);
    mx_send(chat->ssl, dtp);
    mx_free_request(&dtp);
    mx_reset_addroom(NULL, chat->builder);
    (void)btn;
}

static void connect_addroom(t_chat *chat) {
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_addroom_apply"));

    g_signal_connect(btn, "clicked", G_CALLBACK(mx_req_addroom), chat);
}

static bool check_connection(t_chat *chat) {
    if (chat->auth_token) {
        mx_start_main_window(chat);
        return false;
    }
    return true;
}

void mx_init_gui(t_chat *chat) {
    g_idle_add((GSourceFunc)check_connection, chat);
    mx_connect_authorization(chat);
    connect_addroom(chat);
}
