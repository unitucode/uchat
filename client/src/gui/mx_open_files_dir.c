#include "client.h"

void mx_open_files_dir(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, MX_LOCAL_ROOMS);
    t_gmsg *gmsg = g_object_get_data(G_OBJECT(btn), "gmsg");
    t_signal_data *data = g_object_get_data(G_OBJECT(gmsg->row_msg),
                                            "sigdata");

    mx_select_msg(NULL, NULL, data);
    if (g_file_test(gmsg->msg, G_FILE_TEST_EXISTS))
        system("open files/");
    else
        mx_download_file(groom->id, gmsg->message_id, chat);
}
