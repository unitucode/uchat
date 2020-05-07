#include "server.h"

int main(int argc, char **argv) {
    t_chat *chat = mx_init_chat(argc, argv);
    t_client *client = NULL;

    mx_logger(MX_LOG_FILE, LOGMSG,
              "started server pid[%d]: %s %s\n", getpid(), argv[0], argv[1]);
    while (1) {
        client = mx_new_client(chat->len);
        client->socket_fd = mx_accept(chat->listen_fd,
                                      client->cliaddr, &client->len);
        client->chat = chat;
        mx_connect_client(client);
    }
}
