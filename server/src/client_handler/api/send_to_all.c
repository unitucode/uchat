#include "server.h"

static void send_to_all(gpointer data, gpointer user_data) {
    t_send_helper *send_helper = (t_send_helper*)user_data;
    GHashTable *table = send_helper->table;
    GDataOutputStream *out = g_hash_table_lookup(table, data);

    if (out)
        mx_send(out, send_helper->data);
    (void)data;
}

void mx_send_to_all(t_dtp *data, t_client *client, guint64 room_id) {
    GList *list = mx_get_users_in_room(client->info->database, room_id);
    t_send_helper *send_helper = g_malloc0(sizeof(t_send_helper));

    send_helper->data = data;
    send_helper->table = client->info->users;
    g_list_foreach(list, send_to_all, send_helper);
    g_free(send_helper);
}
