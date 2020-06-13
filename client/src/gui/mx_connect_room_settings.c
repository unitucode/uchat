#include "client.h"

static void set_room_sett(GtkButton *btn, t_chat *chat) {
    GtkEntry *name = GTK_ENTRY(gtk_builder_get_object(chat->builder,
                                                      "entry_roomsett_name"));
    GObject *desc = gtk_builder_get_object(chat->builder, "buffer_room_desc");
    t_groom *groom = mx_get_selected_groom(chat->builder);

    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(desc), groom->desc, -1);
    gtk_entry_set_text(name, groom->room_name);
    (void)btn;
}

static void req_room_sett(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder);
    t_dtp *dtp = NULL;
    char *new_name = mx_entry_get_text("entry_roomsett_name",
                                              chat->builder);
    char *new_desc = mx_get_buffer_text("buffer_room_desc", chat->builder);

    if (strcmp(groom->room_name, new_name)) {
        dtp = mx_upd_room_name_request(groom->id, new_name);
        mx_send(chat->ssl, dtp);
        mx_free_request(&dtp);
    }
    if (!groom->desc || strcmp(groom->desc, new_desc)) {
        dtp = mx_upd_room_desc_request(groom->id, new_desc);
        mx_send(chat->ssl, dtp);
        mx_free_request(&dtp);
    }
    (void)btn;
}

static void req_room_del(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder);
    t_dtp *dtp = mx_del_room_request(groom->id);
    puts("WORK");
    mx_send(chat->ssl, dtp);
    mx_free_request(&dtp);
    (void)btn;
}

void mx_connect_room_settings(t_chat *chat) {
    GObject *btn_sett = gtk_builder_get_object(chat->builder,
                                               "btn_roomsett");
    GObject *btn_apply = gtk_builder_get_object(chat->builder,
                                                "btn_roomsett_apply");
    GObject *btn_delete = gtk_builder_get_object(chat->builder,
                                                  "btn_roomsett_delete");

    g_signal_connect(btn_sett, "clicked", G_CALLBACK(set_room_sett), chat);
    g_signal_connect(btn_apply, "clicked", G_CALLBACK(req_room_sett), chat);
    g_signal_connect(btn_delete, "clicked", G_CALLBACK(req_room_del), chat);
}
