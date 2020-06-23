#include "client.h"
#include "time.h"

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
    guint64 date = g_get_real_time();
    GTimeZone *time_zone = g_time_zone_new_local();
    guint64 local = 3 * 60 * 60 * 100 * 100;
    local *= 100;
    date += local;
    // g_print("%s\n", mx_get_string_time(date / 1000, MX_TIME_LONG));
    // g_print("%s\n", mx_get_string_time(date / 1000, MX_TIME_SHORT));
    exit(0);
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
