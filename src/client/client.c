#include "client.h"

static int sockfd;
static FILE *fp;
static int done;

void login(SSL *ssl) {
    char login[1024] = {0};
    char password[1024] = {0};
    t_pds *pass_request = NULL;
    t_pds *login_requset = NULL;

    printf("Enter your login: ");
    fgets(login, 1024, fp);
    printf("Enter your password: ");
    fgets(password, 1024, fp);
    pass_request = mx_request_creation(-1, MX_PASSWORD, password);
    login_requset = mx_request_creation(-1, MX_LOGIN, login);
    mx_send(ssl, login_requset);
    mx_send(ssl, pass_request);
    mx_free_request_struct(&pass_request);
    mx_free_request_struct(&login_requset);
}

void *copyto(void *arg) {
    char sendline[1024];
    t_pds *request = NULL;
    SSL *ssl = (SSL*)arg;
    system("leaks -q uchat");

    while (fgets(sendline, 1024, fp) != NULL) {
        if (!strcmp(sendline, "login\n")) {
            login(ssl);
        }
        else {
            request = mx_request_creation(/*Room id*/1, MX_USER_COUNT, sendline); // Protocol creation
            mx_send(ssl, request);
            mx_free_request_struct(&request);
        }
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
    while (SSL_read(ssl, buf, sizeof(buf))) {
        t_pdl *pdl = mx_request_decode(buf);
        if (pdl->type == MX_ERR_MSG)
            printf("ERROR: %s\n", pdl->data);
        if (pdl->type == MX_TOKEN_AUTH)
            printf("token = %s\n", pdl->data);
    }

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

