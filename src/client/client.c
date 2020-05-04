#include "client.h"

static int sockfd;
static FILE *fp;
static int done;

void *copyto(void *arg) {
    char sendline[1024];
    arg = NULL;
    while (fgets(sendline, 1024, fp) != NULL)
        write(sockfd, sendline, strlen(sendline));
    
    shutdown(sockfd, SHUT_WR);
    done = 1;
    return NULL;
}

void str_cli(FILE *fp_arg, int sockfd_arg) {
    char *recvline = mx_malloc(1025);
    pthread_t tid;

    sockfd = sockfd_arg;
    fp = fp_arg;
    mx_pthread_create(&tid, NULL, copyto, NULL);

    FILE *fd = fdopen(sockfd, "r");
    size_t len = 0;
    while (getline(&recvline, &len, fd) > 0)
        fputs(recvline, stdout);

    if (done == 0)
        exit(1);
}


int main(int argc, char **argv) {
    int sockfd;

    if (argc != 3) {
        printf("usage\n");
        exit(1);
    }
    sockfd = mx_tcp_connect(argv[1], argv[2]);
    str_cli(stdin, sockfd);
}

