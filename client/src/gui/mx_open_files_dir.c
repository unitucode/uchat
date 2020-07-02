#include "client.h"

void mx_open_file_folder(gchar *filename) {
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

static gboolean show_image_viewer(gchar *file_path, GtkBuilder *builder) {
    GObject *viewer = gtk_builder_get_object(builder, "popup_image_viewer");
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(file_path, 800,
                                                         -1, NULL);
    GObject *img = gtk_builder_get_object(builder, "img_view");

    if (g_str_has_suffix(file_path, ".png")
        || g_str_has_suffix(file_path, ".jpg")) {
        mx_widget_set_visibility(GTK_WIDGET(viewer), TRUE);
        gtk_image_set_from_pixbuf(GTK_IMAGE(img), GDK_PIXBUF(pixbuf));
        return TRUE;
    }
    else if (g_str_has_suffix(file_path, ".gif")) {
        mx_widget_set_visibility(GTK_WIDGET(viewer), TRUE);
        gtk_image_set_from_animation(GTK_IMAGE(img), gdk_pixbuf_animation_new_from_file(file_path, NULL));
        return TRUE;
    }
    return FALSE;
}

void mx_open_files_dir(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, MX_LOCAL_ROOMS);
    t_gmsg *gmsg = g_object_get_data(G_OBJECT(btn), "gmsg");
    t_signal_data *data = g_object_get_data(G_OBJECT(gmsg->row_msg),
                                            "sigdata");
    GtkImage *img = GTK_IMAGE(gtk_button_get_image(btn));

    mx_select_msg(NULL, NULL, data);
    if (g_file_test(gmsg->msg, G_FILE_TEST_EXISTS)) {
        if (!show_image_viewer(gmsg->msg, chat->builder))
            mx_open_file_folder(gmsg->msg);
    }
    else {
        mx_download_file(groom->id, gmsg->message_id, chat);
        gtk_image_set_from_icon_name(img, "document", GTK_ICON_SIZE_DND);
    }
}
