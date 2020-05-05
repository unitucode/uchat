#include "server.h"

static void *doit(void *arg);

int main(int argc, char **argv) {
    int listen_fd = 0;
    pthread_t tid = 0;
    struct sockaddr *cliaddr = NULL;
    t_client *client = mx_new_client();
    t_list *list = mx_new_list();

    if (argc == 2) {
        listen_fd = mx_tcp_listen(argv[1], &client->len);
    }
    else {
        printf("usage");
        exit(1);
    }
    client->cliaddr = mx_malloc(client->len);

    while (1) {
        client->socket_fd = mx_accept(listen_fd, cliaddr, &client->len);
        mx_get_client_info(client);
        mx_push_node(list, client, MX_LIST_BACK);
        mx_pthread_create(&tid, NULL, &doit, list);
    }
}

void str_echo(int sockfd) {
    ssize_t n;
    char buf[1024];

again:
    while ((n = read(sockfd, buf, 1024)) > 0)
        write(sockfd, buf, n);
    
    if (n < 0 && errno == EINTR)
        goto again;
    else if (n < 0)
        exit(1);

}

static void *doit(void *arg) {
    t_list *list = (t_list*)arg;
    t_client *client = (t_client *)list->head->data;
    printf("connected %s\n", client->ip);
    pthread_detach(pthread_self());
    str_echo(client->socket_fd);
    mx_close(client->socket_fd);
    return NULL;
}
