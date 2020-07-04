#include "client.h"

/*
 * Function: change_working_dir
 * -------------------------------
 * Changes working directory to MX_CLIENT if its exist
 * and create files directory for downloaded files
 */
static void change_working_dir(void) {
    #ifdef MX_CLIENT
    if (chdir(MX_CLIENT)) {
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_ERROR,
                  "No working directory mx_client");
    }
    if (g_mkdir_with_parents(MX_FILES_DIR, 0755)) {
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_ERROR,
                  "No files directory mx_files_dir");
    }
    #else
    mx_logger(MX_LOG_FILE, LOGERR, "No working directory");
    #endif
}

static gboolean is_valid(gint argc) {
    if (argc != 3) {
        g_printerr("Usage: ./uchat <ip,domen> <port>\n");
        return FALSE;
    }
    return TRUE;
}

gint main(gint argc, char **argv) {
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
    chat->cli_conn = client;
    mx_init_gui(chat);
    mx_start_gui(chat);
    return 0;
}
