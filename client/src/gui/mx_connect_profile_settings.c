#include "client.h"

void mx_show_user_info(GtkBuilder *builder, gchar *login, gchar *desc) {
    GObject *desc_info = gtk_builder_get_object(builder, "buffer_user_desc");
    GObject *login_info = gtk_builder_get_object(builder,
                                                 "label_user_info_login");

    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(desc_info), desc, -1);
    gtk_label_set_text(GTK_LABEL(login_info), login);
}

static void req_get_member_info(GObject *popup, t_chat *chat) {
    t_dtp *dtp = mx_member_info_request((int)g_object_get_data(popup,
                                                               "member_id"));

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
}

static void req_edit_desc(GtkButton *btn, t_chat *chat) {
    gchar *desc = mx_get_buffer_text("buffer_profile_desc", chat->builder);
    t_dtp *dtp = NULL;

    dtp = mx_upd_user_desc_request(desc);
    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    (void)btn;
}

static void req_logout(GtkButton *btn, t_chat *chat) {
    t_dtp *logout = mx_log_out_request(chat->auth_token);

    mx_send(chat->out, logout);
    mx_free_request(&logout);
    (void)btn;
}

static void set_profile_info(GtkButton *btn, t_chat *chat) {
    GObject *label_login = gtk_builder_get_object(chat->builder,
                                                  "label_user_login");
    GObject *buff_desc = gtk_builder_get_object(chat->builder,
                                                "buffer_user_desc");

    gtk_label_set_text(GTK_LABEL(label_login), chat->login);
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buff_desc), chat->desc, -1);
    (void)btn;
}

void mx_connect_profile_settings(t_chat *chat) {
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_logout"));
    GtkButton *edit = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                        "btn_edit_profile"));
    GObject *popup = gtk_builder_get_object(chat->builder, "popup_user_info");
    GObject *sett = gtk_builder_get_object(chat->builder, "btn_profile_sett");

    g_signal_connect(btn, "clicked", G_CALLBACK(req_logout), chat);
    g_signal_connect(edit, "clicked", G_CALLBACK(req_edit_desc), chat);
    g_signal_connect(popup, "show", G_CALLBACK(req_get_member_info), chat);
    g_signal_connect(sett, "clicked", G_CALLBACK(set_profile_info), chat);
}
