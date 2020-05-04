#include "server.h"

static void *doit(void *arg);

int main(int argc, char **argv) {
    int listen_fd, *iptr;
    pthread_t tid;
    socklen_t addrlen, len;
    struct sockaddr *cliaddr;

    if (argc == 2) {
        listen_fd = mx_tcp_listen(argv[1], &addrlen);
    }
    else {
        printf("usage");
        exit(1);
    }
    cliaddr = mx_malloc(addrlen);

    while (1) {
        len = addrlen;
        iptr = mx_malloc(sizeof(int));
        *iptr = mx_accept(listen_fd, cliaddr, &len);
        mx_pthread_create(&tid, NULL, &doit, iptr);
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
    int connfd = *((int *)arg);
    printf("connfd = %d\n", connfd);
    free(arg);
    pthread_detach(pthread_self());
    str_echo(connfd);
    mx_close(connfd);
    return NULL;
}
