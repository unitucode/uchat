#include "server.h"

int main(int argc, char **argv) {
    t_chat *chat = mx_init_chat(argc, argv);
    t_client *client = NULL;

    mx_logger(MX_LOG_FILE, LOGMSG, "started server: %s %s\n", argv[0], argv[1]);
    while (1) {
        client = mx_new_client(chat->len);
        client->socket_fd = mx_accept(chat->listen_fd, client->cliaddr, &client->len);
        mx_get_client_info(client);
        mx_push_node(chat->clients, client, MX_LIST_BACK);
        chat->current_client = client;
        mx_pthread_create(&client->tid, NULL, &client_handler, chat);
    }
}
