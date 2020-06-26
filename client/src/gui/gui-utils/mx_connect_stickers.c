#include "client.h"

void send_sticker_1(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, 
                                           MX_LOCAL_ROOMS);
    t_dtp *dtp = mx_sticker_request("racoon_angry", groom->id);

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    (void)btn;
}


void send_sticker_2(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, 
                                           MX_LOCAL_ROOMS);
    t_dtp *dtp = mx_sticker_request("racoon_happy", groom->id);

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    (void)btn;
}

void send_sticker_3(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, 
                                           MX_LOCAL_ROOMS);
    t_dtp *dtp = mx_sticker_request("racoon_wow", groom->id);

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    (void)btn;
}

void send_sticker_4(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, 
                                           MX_LOCAL_ROOMS);
    t_dtp *dtp = mx_sticker_request("racoon_tounge", groom->id);

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    (void)btn;
}

void send_sticker_5(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, 
                                           MX_LOCAL_ROOMS);
    t_dtp *dtp = mx_sticker_request("duck_angry", groom->id);

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    (void)btn;
}

void send_sticker_6(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, 
                                           MX_LOCAL_ROOMS);
    t_dtp *dtp = mx_sticker_request("duck_happy", groom->id);

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    (void)btn;
}

void send_sticker_7(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, 
                                           MX_LOCAL_ROOMS);
    t_dtp *dtp = mx_sticker_request("duck_wow", groom->id);

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    (void)btn;
}

void send_sticker_8(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, 
                                           MX_LOCAL_ROOMS);
    t_dtp *dtp = mx_sticker_request("duck_tounge", groom->id);

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    (void)btn;
}

void send_sticker_9(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, 
                                           MX_LOCAL_ROOMS);
    t_dtp *dtp = mx_sticker_request("bear_angry", groom->id);

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    (void)btn;
}

void send_sticker_10(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, 
                                           MX_LOCAL_ROOMS);
    t_dtp *dtp = mx_sticker_request("bear_happy", groom->id);

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    (void)btn;
}

void send_sticker_11(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, 
                                           MX_LOCAL_ROOMS);
    t_dtp *dtp = mx_sticker_request("bear_wow", groom->id);

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    (void)btn;
}

void send_sticker_12(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, 
                                           MX_LOCAL_ROOMS);
    t_dtp *dtp = mx_sticker_request("bear_tounge", groom->id);

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    (void)btn;
}

void mx_connect_stickers(t_chat *chat) {
    GObject *sticker_1 = gtk_builder_get_object(chat->builder, "sticker_1");
    GObject *sticker_2 = gtk_builder_get_object(chat->builder, "sticker_2");
    GObject *sticker_3 = gtk_builder_get_object(chat->builder, "sticker_3");
    GObject *sticker_4 = gtk_builder_get_object(chat->builder, "sticker_4");
    GObject *sticker_5 = gtk_builder_get_object(chat->builder, "sticker_5");
    GObject *sticker_6 = gtk_builder_get_object(chat->builder, "sticker_6");
    GObject *sticker_7 = gtk_builder_get_object(chat->builder, "sticker_7");
    GObject *sticker_8 = gtk_builder_get_object(chat->builder, "sticker_8");
    GObject *sticker_9 = gtk_builder_get_object(chat->builder, "sticker_9");
    GObject *sticker_10 = gtk_builder_get_object(chat->builder, "sticker_10");
    GObject *sticker_11 = gtk_builder_get_object(chat->builder, "sticker_11");
    GObject *sticker_12 = gtk_builder_get_object(chat->builder, "sticker_12");

    g_signal_connect(sticker_1, "clicked",  G_CALLBACK(send_sticker_1), chat);
    g_signal_connect(sticker_2, "clicked",  G_CALLBACK(send_sticker_2), chat);
    g_signal_connect(sticker_3, "clicked",  G_CALLBACK(send_sticker_3), chat);
    g_signal_connect(sticker_4, "clicked",  G_CALLBACK(send_sticker_4), chat);
    g_signal_connect(sticker_5, "clicked",  G_CALLBACK(send_sticker_5), chat);
    g_signal_connect(sticker_6, "clicked",  G_CALLBACK(send_sticker_6), chat);
    g_signal_connect(sticker_7, "clicked",  G_CALLBACK(send_sticker_7), chat);
    g_signal_connect(sticker_8, "clicked",  G_CALLBACK(send_sticker_8), chat);
    g_signal_connect(sticker_9, "clicked",  G_CALLBACK(send_sticker_9), chat);
    g_signal_connect(sticker_10, "clicked",  G_CALLBACK(send_sticker_10), chat);
    g_signal_connect(sticker_11, "clicked",  G_CALLBACK(send_sticker_11), chat);
    g_signal_connect(sticker_12, "clicked",  G_CALLBACK(send_sticker_12), chat);
}
