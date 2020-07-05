#include "client.h"

void mx_clear_history_set_roomname(GtkButton *btn, GtkBuilder *builder) {
    t_groom *groom = mx_get_selected_groom(builder,  MX_LOCAL_ROOMS);
    GObject *label = gtk_builder_get_object(builder,
                                            "label_clear_history_roomname");
    
    gtk_label_set_text(GTK_LABEL(label), groom->room_name);
    (void)btn;
}

void mx_set_room_sett(GtkButton *btn, t_chat *chat) {
    GtkEntry *name = GTK_ENTRY(gtk_builder_get_object(chat->builder,
                                                      "entry_roomsett_name"));
    GObject *desc = gtk_builder_get_object(chat->builder, "buffer_room_desc");
    t_groom *groom = mx_get_selected_groom(chat->builder, MX_LOCAL_ROOMS);

    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(desc), groom->desc, -1);
    gtk_entry_set_text(name, groom->room_name);
    gtk_editable_set_position(GTK_EDITABLE(name), -1);
    (void)btn;
}

void mx_req_room_sett(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, MX_LOCAL_ROOMS);
    t_dtp *dtp = NULL;
    char *new_name = g_strndup(mx_entry_get_text("entry_roomsett_name",
                                                 chat->builder),
                                                 MX_MAX_ROOM_NAME);
    char *new_desc = mx_get_buffer_text("buffer_room_desc", chat->builder);

    mx_trim_message(&new_desc);
    if (g_strcmp0(groom->room_name, new_name)) {
        dtp = mx_upd_room_name_request(groom->id, new_name);
        mx_send(chat->out, dtp);
        mx_free_request(&dtp);
    }
    if (!groom->desc || g_strcmp0(groom->desc, new_desc)) {
        dtp = mx_upd_room_desc_request(groom->id, new_desc);
        mx_send(chat->out, dtp);
        mx_free_request(&dtp);
    }
    (void)btn;
}

void mx_req_room_clear(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, MX_LOCAL_ROOMS);
    t_dtp *dtp = mx_del_hist_request(groom->id);

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    (void)btn;
}

void mx_req_room_del(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, MX_LOCAL_ROOMS);
    t_dtp *dtp = mx_del_room_request(groom->id);

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    (void)btn;
}
