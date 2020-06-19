#include "client.h"

static void change_working_dir(void) {
    #ifdef MX_CLIENT
    if (chdir(MX_CLIENT)) {
        mx_elogger(NULL, LOGERR,
                   "No working directory %s\n", MX_CLIENT);
    }
    #else
    mx_elogger(NULL, LOGERR, "No working directory");
    #endif
}


int main(int argc, char **argv) {
    GError *error = NULL;
    GSocketConnection *connection = NULL;
    GSocketClient *client = g_socket_client_new();
    t_chat *chat = NULL;

    change_working_dir();
    if (argc != 3) {
        g_printerr("Usage: ./uchat <ip,domen> <port>\n");
        return -1;
    }
    connection = g_socket_client_connect_to_host(client, argv[1], g_ascii_strtoll(argv[2], NULL, 10), NULL, &error);
    if (!connection || error) {
        g_printerr("Invalid port or ip\n");
        return -1;
    }
    chat = mx_init_chat(connection, argc, argv);
    chat->cli_conn = g_object_ref(client);
    mx_init_gui(chat);
    mx_start_gui(chat);
    return 0;
}
