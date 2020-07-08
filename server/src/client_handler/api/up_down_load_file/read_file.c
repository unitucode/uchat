#include "api.h"

static gboolean is_valid(GFile *file, gsize size, gsize bytes) {
    if (file && bytes != size) {
        if (g_file_query_exists(file, NULL))
            g_file_delete(file, NULL, NULL);
        return FALSE;
    }
    if (file && g_file_query_file_type(file, G_FILE_QUERY_INFO_NONE, NULL)
        != G_FILE_TYPE_REGULAR) {
        if (g_file_query_exists(file, NULL))
            g_file_delete(file, NULL, NULL);
        return FALSE;
    }
    return TRUE;
}

static void send_ready(t_client *client) {
    cJSON *ready = cJSON_CreateObject();
    t_dtp *ready_dtp = NULL;

    cJSON_AddNumberToObject(ready, "type", RQ_READY_READ);
    ready_dtp = mx_get_transport_data(ready);
    mx_send(client->out, ready_dtp);
    mx_free_request(&ready_dtp);
}

static gboolean read_file(t_client *client, GFile *file, gsize size,
                          GFileOutputStream *out) {
    gsize bytes = 0;

    if (size <= MX_MAX_FILE_SIZE) {
        bytes = g_output_stream_splice(
            G_OUTPUT_STREAM(out), client->in_s,
            G_OUTPUT_STREAM_SPLICE_CLOSE_TARGET,
            NULL, NULL);
    }
    if (!is_valid(file, size, bytes))
        return FALSE;
    return TRUE;
}

gboolean mx_read_file(t_client *client, gsize size, char *name) {
    GFile *file = g_file_new_for_path(name);
    GFileOutputStream *out = g_file_create(file, G_FILE_CREATE_NONE,
                                           NULL, NULL);

    send_ready(client);
    if (!out || !read_file(client, file, size, out)) {
        g_object_unref(file);
        return FALSE;
    }
    g_object_unref(file);
    return TRUE;
}
