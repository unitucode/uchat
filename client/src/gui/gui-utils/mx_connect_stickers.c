#include "client.h"

static void send_sticker(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder,
                                           MX_LOCAL_ROOMS);
    t_dtp *dtp = NULL;
    GtkImage *image = GTK_IMAGE(gtk_button_get_image(btn));
    gchar *sticker_name;

    gtk_image_get_icon_name(image, (const gchar**)&sticker_name, NULL);
    dtp = mx_sticker_request(sticker_name, groom->id);
    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    mx_reset_messege_room(NULL, chat->builder);
}

static void connect_stickers_1(t_chat *chat) {
    GObject *sticker_1 = gtk_builder_get_object(chat->builder, "sticker_1");
    GObject *sticker_2 = gtk_builder_get_object(chat->builder, "sticker_2");
    GObject *sticker_3 = gtk_builder_get_object(chat->builder, "sticker_3");
    GObject *sticker_4 = gtk_builder_get_object(chat->builder, "sticker_4");

    g_signal_connect(sticker_1, "clicked",  G_CALLBACK(send_sticker), chat);
    g_signal_connect(sticker_2, "clicked",  G_CALLBACK(send_sticker), chat);
    g_signal_connect(sticker_3, "clicked",  G_CALLBACK(send_sticker), chat);
    g_signal_connect(sticker_4, "clicked",  G_CALLBACK(send_sticker), chat);
}

static void connect_stickers_2(t_chat *chat) {
    GObject *sticker_5 = gtk_builder_get_object(chat->builder, "sticker_5");
    GObject *sticker_6 = gtk_builder_get_object(chat->builder, "sticker_6");
    GObject *sticker_7 = gtk_builder_get_object(chat->builder, "sticker_7");
    GObject *sticker_8 = gtk_builder_get_object(chat->builder, "sticker_8");

    g_signal_connect(sticker_5, "clicked",  G_CALLBACK(send_sticker), chat);
    g_signal_connect(sticker_6, "clicked",  G_CALLBACK(send_sticker), chat);
    g_signal_connect(sticker_7, "clicked", G_CALLBACK(send_sticker), chat);
    g_signal_connect(sticker_8, "clicked", G_CALLBACK(send_sticker), chat);
}

static void connect_stickers_3(t_chat *chat) {
    GObject *sticker_9 = gtk_builder_get_object(chat->builder, "sticker_9");
    GObject *sticker_10 = gtk_builder_get_object(chat->builder, "sticker_10");
    GObject *sticker_11 = gtk_builder_get_object(chat->builder, "sticker_11");
    GObject *sticker_12 = gtk_builder_get_object(chat->builder, "sticker_12");

    g_signal_connect(sticker_9, "clicked", G_CALLBACK(send_sticker), chat);
    g_signal_connect(sticker_10, "clicked", G_CALLBACK(send_sticker), chat);
    g_signal_connect(sticker_11, "clicked", G_CALLBACK(send_sticker), chat);
    g_signal_connect(sticker_12, "clicked", G_CALLBACK(send_sticker), chat);
}

void mx_connect_stickers(t_chat *chat) {
    connect_stickers_1(chat);
    connect_stickers_2(chat);
    connect_stickers_3(chat);
}
