#include "client.h"

// static int sockfd;
// static int done;

// void *copyto(void *arg) {
//     char sendline[1024];
//     t_dtp *request = NULL;
//     SSL *ssl = (SSL*)arg;
//     system("leaks -q uchat");
//     while (fgets(sendline, 1024, fp)) {
//         if (!strcmp("signup\n", sendline))
//             mx_signup(ssl);
//         else if (!strcmp("login\n", sendline))
//             mx_login(ssl);
//         else {
//             request = mx_msg_request(1, NULL, sendline);
//             // printf("req = %s len = %zu len = %zu\n", request->str, strlen(request->str), request->len);
//             mx_send(ssl, request);
//             mx_free_request(&request);
//             bzero(sendline, sizeof(sendline));
//         }
//     }
//     shutdown(sockfd, SHUT_WR);
//     done = 1;
//     return NULL;
// }

// void str_cli(FILE *fp_arg, SSL *ssl) {
//     // pthread_t tid;
//     char buf[1025];
//     t_dtp *dtp = NULL;

//     bzero(&buf, sizeof(buf));
//     fp = fp_arg;
//     // mx_pthread_create(&tid, NULL, copyto, ssl);
//     while ((dtp = mx_recv(ssl))) {
//         printf("%s\n", dtp->str);
//         mx_free_request(&dtp);
//     }

//     if (done == 0)
//         exit(1);
// }

static void change_working_dir(void) {
    #ifdef MX_CLIENT
    if (chdir(MX_CLIENT)) {
        mx_elogger(NULL, LOGERR,
                   "No working directory %s\n", MX_CLIENT);
    }
    #else
    mx_elogger(NULL, LOGERR, "No working directory");
    #endif
}

void test(t_chat *chat) {
    // char *login = "admin4";
    char pass[33];

    pass[32] = '\0';
    mx_md5(pass, (const unsigned char*)"admin", 5);
    t_dtp *signup = mx_token_request("89f234ad6490edeec3f09057afc2dbaf123456789");
    mx_send(chat->ssl, signup);
    mx_free_request(&signup);
}

int main(int argc, char **argv) {
    int sockfd;
    t_ssl_con *ssl = NULL;
    t_chat *chat = mx_init_chat();

    change_working_dir();
    if (argc != 3) {
        printf("usage\n");
        exit(1);
    }
    ssl = mx_init_ssl(CLIENT);
    mx_logger(MX_LOG_FILE, LOGMSG, "started client: %s %s\n", argv[1], argv[2]);
    sockfd = mx_tcp_connect(argv[1], argv[2]);
    ssl->ssl = SSL_new(ssl->ctx);
    chat->ssl = ssl->ssl;
    SSL_set_fd(ssl->ssl, sockfd);
    if (SSL_connect(ssl->ssl) == -1) {
        mx_elogger(MX_LOG_FILE, LOGERR, "SSL_connect failded\n");
    }
    chat->builder = mx_init_window(argc, argv);
    mx_init_gui(chat);
    mx_init_receiver(chat);
    // test(chat);
    mx_start_window(chat);
}
