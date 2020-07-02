#include "client.h"

static void open_dir(gchar *filename) {
    gchar *path = g_path_get_dirname(filename);
    GFile *file = g_file_new_for_path(path);
    gchar *uri = NULL;

    if (file)
        uri = g_file_get_uri(file);
    if (uri) {
        g_app_info_launch_default_for_uri(uri, NULL, NULL);
        g_free(path);
        g_free(uri);
    }
    if (file)
        g_object_unref(file);
}

void mx_open_files_dir(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, MX_LOCAL_ROOMS);
    t_gmsg *gmsg = g_object_get_data(G_OBJECT(btn), "gmsg");
    t_signal_data *data = g_object_get_data(G_OBJECT(gmsg->row_msg),
                                            "sigdata");
    GtkImage *img = GTK_IMAGE(gtk_button_get_image(btn));

    mx_select_msg(NULL, NULL, data);
    if (g_file_test(gmsg->msg, G_FILE_TEST_EXISTS)) {
        open_dir(gmsg->msg);
    }
    else {
        mx_download_file(groom->id, gmsg->message_id, chat);
        gtk_image_set_from_icon_name(img, "document", GTK_ICON_SIZE_DND);
    }
}
