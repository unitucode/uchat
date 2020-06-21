#include "client.h"

static void req_addroom(GtkButton *btn, t_chat *chat) {
    gchar *room_name = mx_get_buffer_text("buffer_roomname", chat->builder);
    t_dtp *dtp = mx_new_room_request(room_name, "", DB_GLOBAL_CHAT);

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    mx_reset_addroom(NULL, chat->builder);
    (void)btn;
}

void mx_connect_addroom(t_chat *chat) {
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_addroom_apply"));

    g_signal_connect(btn, "clicked", G_CALLBACK(req_addroom), chat);
}
