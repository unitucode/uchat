#include "client.h"

void mx_connect_profile_settings(t_chat *chat) {
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_logout"));
    GtkButton *edit = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                        "btn_edit_profile"));
    GObject *popup = gtk_builder_get_object(chat->builder, "popup_user_info");
    GObject *sett = gtk_builder_get_object(chat->builder, "btn_profile_sett");

    g_signal_connect(btn, "clicked", G_CALLBACK(mx_req_logout), chat);
    g_signal_connect(edit, "clicked", G_CALLBACK(mx_req_edit_desc), chat);
    g_signal_connect(popup, "show", G_CALLBACK(mx_req_get_member_info), chat);
    g_signal_connect(sett, "clicked", G_CALLBACK(mx_set_profile_info), chat);
}
