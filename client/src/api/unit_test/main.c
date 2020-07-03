#include <gtk/gtk.h>
#include "client.h"

int main (int argc, char **argv) {
    GSocketConnection *connection = NULL;
    GSocketClient *client = g_socket_client_new();
    t_chat *chat = NULL;

    change_working_dir();
    if (!is_valid(argc))
        return -1;
    connection = g_socket_client_connect_to_host(
        client, argv[1], g_ascii_strtoll(argv[2], NULL, 10), NULL, NULL);
    if (!connection) {
        g_printerr("Invalid port or ip\n");
        return -1;
    }
    chat = mx_init_chat(connection, argc, argv);
    mx_gui_unit_test(chat, argc, argv);
    return 0;
}
