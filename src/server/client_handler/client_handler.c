#include "server.h"

static void str_echo(int sockfd, t_list *list, t_client *cur_client) {
    ssize_t n;
    char buf[1024];

again:
    while ((n = read(sockfd, buf, 1024)) > 0) {
        for (t_node *cur = list->head; cur; cur = cur->next) {
            t_client *client = (t_client*)cur->data;
            if (cur_client->socket_fd != client->socket_fd)
                write(client->socket_fd, buf, n);
        }
    }
    
    if (n < 0 && errno == EINTR)
        goto again;
    else if (n < 0)
        exit(1);

}

void *client_handler(void *arg) {
    t_chat *chat = (t_chat*)arg;
    t_list *list = (t_list*)chat->clients;
    t_client *client = chat->current_client;
    pthread_detach(pthread_self());
    str_echo(client->socket_fd, list, client);
    mx_delete_client_list(chat->clients, client);
    system("leaks -q chat_server");
    return NULL;
}
