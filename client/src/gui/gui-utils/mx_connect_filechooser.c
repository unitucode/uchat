#include "client.h"

static void open_file(GtkButton *btn, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, MX_LOCAL_ROOMS);
    GObject *popup = gtk_builder_get_object(chat->builder, "filechooser");
    gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(popup));

    mx_reset_messege_room(NULL, chat->builder);
    mx_upload_file(filename, groom->id, chat);
    g_free(filename);
    (void)btn;
}

void mx_connect_filechooser(t_chat *chat) {
    GObject *btn = gtk_builder_get_object(chat->builder,
                                          "btn_filechooser_open");

    g_signal_connect(btn, "clicked", G_CALLBACK(open_file), chat);
}
