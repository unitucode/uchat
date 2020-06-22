#include "client.h"

void mx_msgcreate_label_login(GtkWidget *box_main, t_gmsg *gmsg) {
    GtkWidget *label_login = gtk_label_new(gmsg->login);

    mx_widget_set_class(label_login, "sender_login");
    gtk_box_pack_start(GTK_BOX(box_main), label_login, FALSE, FALSE, 0);
    gtk_widget_set_halign(label_login, GTK_ALIGN_START);
}

void mx_msgcreate_img_sticker(GtkWidget *box_info,
                              t_gmsg *gmsg, gboolean is_own) {
    gchar *sticker_path = g_strjoin("", MX_STICKER_PATH, gmsg->msg, NULL);
    GtkWidget *sticker = gtk_image_new_from_file(sticker_path);

    if (is_own)
        gtk_box_pack_end(GTK_BOX(box_info), sticker, FALSE, FALSE, 0);
    else
        gtk_box_pack_start(GTK_BOX(box_info), sticker, FALSE, FALSE, 0);
    g_free(sticker_path);
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
    gtk_label_set_text(GTK_LABEL(label_text), gmsg->msg);
    gmsg->label_text = GTK_LABEL(label_text);
    g_object_ref(label_text);
}

void mx_msgcreate_label_time(GtkWidget *box_info,
                             t_gmsg *gmsg, gboolean is_own) {
    GtkWidget *label_time = gtk_label_new(NULL);

    if (is_own)
        gtk_box_pack_end(GTK_BOX(box_info), label_time, FALSE, TRUE, 0);
    else
        gtk_box_pack_start(GTK_BOX(box_info), label_time, FALSE, TRUE, 0);
    gtk_widget_set_halign(label_time, GTK_ALIGN_START);
    gtk_widget_set_valign(label_time, GTK_ALIGN_END);
    gtk_label_set_text(GTK_LABEL(label_time), "13:07");
    gtk_widget_set_tooltip_text(label_time, "24.05.2020    13:37");
    (void)gmsg;
}
