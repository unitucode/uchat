#include "server.h"

static void *doit(void *arg);

int main(int argc, char **argv) {
    int listen_fd = 0;
    pthread_t tid = 0;
    socklen_t len = 0;
    t_list *list = mx_new_list();

    if (argc == 2) {
        listen_fd = mx_tcp_listen(argv[1], &len);
    }
    else {
        printf("usage");
        exit(1);
    }

    while (1) {
        t_client *client = mx_new_client(len);
        client->socket_fd = mx_accept(listen_fd, client->cliaddr, &client->len);
        mx_get_client_info(client);
        printf("connected %s:%s\n", client->ip, client->port);
        mx_push_node(list, client, MX_LIST_BACK);
        mx_pthread_create(&tid, NULL, &doit, list);
    }
}

void str_echo(int sockfd) {
    ssize_t n;
    char buf[1024];

again:
    while ((n = read(sockfd, buf, 1024)) > 0) {
        puts(buf);
        write(sockfd, buf, n);
    }
    
    if (n < 0 && errno == EINTR)
        goto again;
    else if (n < 0)
        exit(1);

}

static void *doit(void *arg) {
    t_list *list = (t_list*)arg;
    t_client *client = (t_client *)list->head->data;
    printf("connected %s:%s\n", client->ip, client->port);
    pthread_detach(pthread_self());
    str_echo(client->socket_fd);
    mx_close(client->socket_fd);
    return NULL;
}
