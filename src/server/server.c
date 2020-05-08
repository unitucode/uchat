#include "server.h"

int main(int argc, char **argv) {
    t_chat *chat = mx_init_chat(argc, argv);
    t_client *client = NULL;
    t_ssl_con *ssl = mx_init_ssl(SERVER);

    mx_logger(MX_LOG_FILE, LOGMSG,
              "started server pid[%d]: %s %s\n", getpid(), argv[0], argv[1]);
    while (1) {
        client = mx_new_client(chat->len);
        client->socket_fd = mx_accept(chat->listen_fd,
                                      client->cliaddr, &client->len);
        ssl->ssl = SSL_new(ssl->ctx);
        SSL_set_fd(ssl->ssl, client->socket_fd);
        client->chat = chat;
        client->ssl = ssl->ssl;
        mx_connect_client(client);
    }
}
