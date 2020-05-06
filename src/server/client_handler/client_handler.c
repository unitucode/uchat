#include "server.h"

static void str_echo(int sockfd, t_list *list) {
    ssize_t n;
    char buf[1024];

    printf("pointer = %p %p\n", (void *)buf, (void *)list);

again:
    while ((n = read(sockfd, buf, 1024)) > 0) {
        for (t_node *cur = list->head; cur; cur = cur->next) {
            printf("[cur data = %s]\n", cur->data);
        }
        write(sockfd, buf, n);
    }
    
    if (n < 0 && errno == EINTR)
        goto again;
    else if (n < 0)
        exit(1);

}

void *client_handler(void *arg) {
    t_chat *chat = (t_chat*)arg;
    t_list *list = (t_list*)chat->clients;
    t_client *client = (t_client *)list->head->data;
    // pthread_detach(pthread_self());
    str_echo(client->socket_fd, list);
    mx_close(client->socket_fd);
    return NULL;
}
