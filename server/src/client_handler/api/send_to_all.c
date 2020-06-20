#include "server.h"

static void send_to_all(gpointer data, gpointer user_data) {
    GDataOutputStream *out = G_DATA_OUTPUT_STREAM(data);

    mx_send(out, user_data);
}

void mx_send_to_all(t_dtp *data, t_client *client) {
    g_list_foreach(client->info->users, send_to_all, data);
}
