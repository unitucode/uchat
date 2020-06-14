#include "client.h"

static void req_test(GtkButton *btn, t_chat *chat) {
    t_dtp *file = mx_upload_file_request("info.log");
    printf("file = %s\n", cJSON_Print(file->json));
    mx_free_request(&file);
    chat++;
    (void)btn;
}

void mx_connect_test_request(t_chat *chat) {
    GtkButton *btn = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_stickers"));

    g_signal_connect(btn, "clicked", G_CALLBACK(req_test), chat);
}
