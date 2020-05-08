#include "client.h"

static int sockfd;
static FILE *fp;
static int done;

void *copyto(void *arg) {
    char sendline[1024];
    t_pds *request = NULL;

    SSL *ssl = (SSL*)arg;
    while (fgets(sendline, 1024, fp) != NULL) {
        request = mx_request_creation(MX_LOGIN, sendline); // Protocol creation
        SSL_write(ssl, request->data, strlen(request->data));
        mx_free_request_struct(&request);
        bzero(sendline, sizeof(sendline));
    }
    shutdown(sockfd, SHUT_WR);
    done = 1;
    return NULL;
}

void str_cli(FILE *fp_arg, SSL *ssl) {
    pthread_t tid;
    char buf[1025];

    bzero(&buf, sizeof(buf));
    fp = fp_arg;
    mx_pthread_create(&tid, NULL, copyto, ssl);
    while (SSL_read(ssl, buf, sizeof(buf)))
        printf("%s", buf);

    if (done == 0)
        exit(1);
}


int main(int argc, char **argv) {
    int sockfd;
    t_ssl_con *ssl = NULL;

    if (argc != 3) {
        printf("usage\n");
        exit(1);
    }
    ssl = mx_init_ssl(CLIENT);
    mx_logger(MX_LOG_FILE, LOGMSG, "started client: %s %s %s\n", argv[0], argv[1], argv[2]);
    sockfd = mx_tcp_connect(argv[1], argv[2]);
    ssl->ssl = SSL_new(ssl->ctx);
    SSL_set_fd(ssl->ssl, sockfd);
    if (SSL_connect(ssl->ssl) == -1) {
        mx_elogger(MX_LOG_FILE, LOGERR, "SSL_connect failded\n");
    }
    str_cli(stdin, ssl->ssl);
}

