#include "client.h"

void mx_connect_message_ctrl(t_chat *chat) {
    GObject *btn_delete = gtk_builder_get_object(chat->builder,
                                                 "btn_delete_msg");
    GObject *btn_edit = gtk_builder_get_object(chat->builder,
                                               "btn_edit_msg");
    GObject *btn_unselect = gtk_builder_get_object(chat->builder,
                                                  "btn_unselect_msg");

    g_signal_connect(btn_delete, "clicked",
                     G_CALLBACK(mx_delete_selected_msgs), chat);
    g_signal_connect(btn_edit, "clicked",
                     G_CALLBACK(mx_show_edit_msg), chat);
    g_signal_connect(btn_unselect, "clicked",
                     G_CALLBACK(mx_unselect_msg), chat->builder);
}
