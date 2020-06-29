#include "client.h"

void mx_msgcreate_label_login(GtkWidget *box_main, t_gmsg *gmsg) {
    GtkWidget *label_login = gtk_label_new(gmsg->login);

    mx_widget_set_class(label_login, "sender_login");
    gtk_box_pack_start(GTK_BOX(box_main), label_login, FALSE, FALSE, 0);
    gtk_widget_set_halign(label_login, GTK_ALIGN_START);
}

void mx_msgcreate_img_sticker(GtkWidget *box_info,
                              t_gmsg *gmsg, gboolean is_own) {
    GtkWidget *sticker = gtk_image_new_from_icon_name(gmsg->msg,
                                                      GTK_ICON_SIZE_DIALOG);

    gtk_image_set_pixel_size(GTK_IMAGE(sticker), 128);
    if (is_own)
        gtk_box_pack_end(GTK_BOX(box_info), sticker, FALSE, FALSE, 0);
    else
        gtk_box_pack_start(GTK_BOX(box_info), sticker, FALSE, FALSE, 0);
}

void mx_msgcreate_label_text(GtkWidget *box_info,
                             t_gmsg *gmsg, gboolean is_own) {
    GtkWidget *label_text = gtk_label_new(NULL);

    if (is_own)
        gtk_box_pack_end(GTK_BOX(box_info), label_text, FALSE, FALSE, 0);
    else
        gtk_box_pack_start(GTK_BOX(box_info), label_text, FALSE, FALSE, 0);
    gtk_label_set_xalign(GTK_LABEL(label_text), 0.00);
    gtk_widget_set_halign(label_text, GTK_ALIGN_START);
    gtk_label_set_line_wrap(GTK_LABEL(label_text), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(label_text), PANGO_WRAP_WORD_CHAR);
    gtk_label_set_markup(GTK_LABEL(label_text), mx_format_text(gmsg->msg));
    gmsg->label_text = GTK_LABEL(label_text);
    g_object_ref(label_text);
}

void mx_msgcreate_label_time(GtkWidget *box_info,
                             t_gmsg *gmsg, gboolean is_own) {
    GtkWidget *label_time = gtk_label_new(NULL);
    gchar *short_time = mx_get_string_time(gmsg->date, MX_TIME_SHORT);
    gchar *long_time = mx_get_string_time(gmsg->date, MX_TIME_LONG);

    if (is_own)
        gtk_box_pack_end(GTK_BOX(box_info), label_time, FALSE, TRUE, 0);
    else
        gtk_box_pack_start(GTK_BOX(box_info), label_time, FALSE, TRUE, 0);
    gtk_widget_set_halign(label_time, GTK_ALIGN_START);
    gtk_widget_set_valign(label_time, GTK_ALIGN_END);
    gtk_label_set_text(GTK_LABEL(label_time), short_time);
    gtk_widget_set_tooltip_text(label_time, long_time);
    g_free(short_time);
    g_free(long_time);
}

void download(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, MX_LOCAL_ROOMS);
    t_gmsg *gmsg = g_object_get_data(G_OBJECT(btn), "gmsg");
    t_dtp *dtp = NULL;

    dtp = mx_download_file_request(groom->id, gmsg->message_id, gmsg->msg);
    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
}

void mx_msgcreate_file(GtkWidget *box_info, t_gmsg *gmsg,
                       gboolean is_own, t_chat *chat) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *btn = gtk_button_new_from_icon_name("document",
                                                   GTK_ICON_SIZE_DIALOG);
    GtkWidget *filename = gtk_label_new(gmsg->msg);

    gtk_widget_set_events(btn,GDK_BUTTON_RELEASE_MASK);
    g_object_set_data(G_OBJECT(btn), "gmsg", gmsg);
    g_signal_connect(btn, "clicked",
                     G_CALLBACK(download), chat);
    gtk_label_set_line_wrap(GTK_LABEL(filename), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(filename), PANGO_WRAP_WORD_CHAR);
    gtk_box_pack_start(GTK_BOX(box), btn, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), filename, FALSE, TRUE, 0);
    if (is_own)
        gtk_box_pack_end(GTK_BOX(box_info), box, FALSE, TRUE, 0);
    else
        gtk_box_pack_start(GTK_BOX(box_info), box, FALSE, TRUE, 0);
}
