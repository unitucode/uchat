#include "client.h"

static void bytes_ready(GObject *source_object, GAsyncResult *res, gpointer user_data) { // ADD ERRORS
    GBytes *bytes = g_file_load_bytes_finish(G_FILE(source_object), res, NULL, NULL);
    GFileInfo *info = g_file_query_info(G_FILE(source_object), "standard::size,standard::name", G_FILE_QUERY_INFO_NONE, NULL, NULL);
    goffset size = g_file_info_get_size(info);
    const char *name = g_file_info_get_name(info);
    t_dtp *upload_file = mx_upload_file_request((char*)name, size);
    t_chat *chat = (t_chat*)user_data;
    
    mx_send(chat->out, upload_file);
    (void)bytes;
}

static void file_ready(GObject *source_object, GAsyncResult *res, gpointer user_data) { //ADD ERRORS
    g_file_load_bytes_async(G_FILE(source_object), NULL, bytes_ready, user_data);
    (void)res;
}

void mx_upload_file(char *path, t_chat *chat) {
    GFile *file = g_file_new_for_path(path);
    g_file_read_async(file, G_PRIORITY_DEFAULT, NULL, file_ready, chat);
}
