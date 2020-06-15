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
    mx_send_request(chat, signup);
    mx_free_request(&signup);
}

bool mx_connect(t_chat *chat) {
    int sockfd = mx_tcp_connect(chat->con_data->argv[1], 
                                chat->con_data->argv[2]);

    if (sockfd == -1)
        return false;
    chat->con_data->ssl->ssl = SSL_new(chat->con_data->ssl->ctx);
    chat->ssl = chat->con_data->ssl->ssl;
    SSL_set_fd(chat->con_data->ssl->ssl, sockfd);
    if (SSL_connect(chat->con_data->ssl->ssl) == -1) {
        mx_logger(MX_LOG_FILE, LOGERR, "SSL_connect failded\n");
        return false;
    }
    return true;
}

int main(int argc, char **argv) {
    t_ssl_con *ssl = NULL;
    t_chat *chat = mx_init_chat();

    change_working_dir();
    if (argc != 3) {
        printf("usage\n");
        exit(1);
    }
    ssl = mx_init_ssl(CLIENT);
    mx_logger(MX_LOG_FILE, LOGMSG, "started client: %s %s\n", argv[1], argv[2]);
    chat->con_data->ssl = ssl;
    chat->con_data->argv = argv;
    if (!mx_connect(chat))
        mx_elogger(MX_LOG_FILE, LOGERR, "SSL_connect failded\n");
    chat->builder = mx_init_window(argc, argv);
    mx_init_gui(chat);
    mx_init_errors(chat);
    mx_init_handlers(chat);
    // test(chat);
    mx_start_gui(chat);
}
