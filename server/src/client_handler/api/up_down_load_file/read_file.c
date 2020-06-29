#include "api.h"

static gboolean is_valid(GFile *file, gsize size, gsize bytes) {
    if (bytes != size) {
        g_file_delete(file, NULL, NULL);
        return FALSE;
    }
    if (g_file_query_file_type(file, G_FILE_QUERY_INFO_NONE, NULL)
        != G_FILE_TYPE_REGULAR) {
        g_file_delete(file, NULL, NULL);
        return FALSE;
    }
    return TRUE;
}

static gboolean read_file(t_client *client, GFile *file, gsize size,
                          GFileOutputStream *out) {
    char buf[MX_BUF_FILE + 1];
    gssize read = 0;
    gsize bytes = 0;

    if (size <= MX_MAX_FILE_SIZE) {
        while ((read = g_input_stream_read(client->in_s, buf, size, NULL,
                                           NULL)) > 0) {
            bytes += read;
            if (bytes > size)
                break;
            if (g_output_stream_write(G_OUTPUT_STREAM(out), buf, read, NULL,
                                      NULL) < 0) {
                break;
            }
        }
    }
    if (!is_valid(file, size, bytes))
        return FALSE;
    return TRUE;
}

gboolean mx_read_file(t_client *client, gsize size, char *name) {
    GFile *file = g_file_new_for_path(name);
    GFileOutputStream *out = g_file_create(file, G_FILE_CREATE_NONE,
                                           NULL, NULL);
    
    if (!out || !read_file(client, file, size, out)) {
        g_object_unref(file);
        return FALSE;
    }
    g_object_unref(file);
    return TRUE;
}
