#include "client.h"

GHashTable *mx_init_stickers() {
    GHashTable *stickers = g_hash_table_new(g_str_hash, g_str_equal);
    GDir *dir = g_dir_open(MX_STICKER_PATH, 0, NULL);
    const gchar *file = NULL;
    gchar *sticker_path = NULL;
    GtkWidget *image = NULL;
    
    while ((file = g_dir_read_name(dir))) {
        if (g_str_has_suffix(file, ".svg")) {
            sticker_path = g_strjoin("", MX_STICKER_PATH, file, NULL);
            image = gtk_image_new_from_file(sticker_path);
            g_hash_table_insert(stickers, g_strdup(file), image);
            g_free(sticker_path);
        }
    }
    return stickers;
}

t_chat *mx_init_chat(GSocketConnection *connection, int argc, char **argv) {
    t_chat *chat = mx_malloc(sizeof(t_chat));
    GOutputStream *out_s = g_io_stream_get_output_stream(G_IO_STREAM(connection));
    GDataOutputStream *out = g_data_output_stream_new(out_s);
    GInputStream *in_s = g_io_stream_get_input_stream(G_IO_STREAM(connection));
    GDataInputStream *in = g_data_input_stream_new(in_s);

    chat->builder = NULL;
    chat->conn = g_object_ref(connection);
    chat->curr_room = NULL;
    chat->auth_token = NULL;
    chat->valid = true;
    chat->login = NULL;
    chat->out = g_object_ref(out);
    chat->in = g_object_ref(in);
    chat->builder = mx_init_window(argc, argv);
    chat->argc = argc;
    chat->argv = argv;
    chat->upl_old_msgs = false;
    chat->stickers = mx_init_stickers();
    chat->msg_placeholder = true;
    mx_init_handlers(chat);
    mx_init_errors(chat);
    g_data_input_stream_read_line_async(in, G_PRIORITY_DEFAULT, NULL, mx_receiver, chat);
    return chat;
}
