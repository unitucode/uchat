#include "utils.h"

static int message_size(SSL *ssl) {
    t_pdl *pdl = NULL;
    char buf[MX_BUF_SIZE];
    size_t bytes = 0;
    int size = -1;

    while ((bytes = SSL_read(ssl, buf, sizeof(buf))) > 0) {
        pdl = mx_request_decode(buf);
        if (pdl->type == MX_SIZE_MSG) {
            size = atoi(pdl->data);
            break;
        }
        mx_free_decode_struct(&pdl);
    }
    if (pdl)
        mx_free_decode_struct(&pdl);
    return size;
}

t_pdl *mx_recv(SSL *ssl) {
    t_pdl *pdl = NULL;
    int size = 0;

    if ((size = message_size(ssl)) != -1) {
        char buf[size + 1];

        buf[size + 1] = '\0';
        if (SSL_read(ssl, buf, sizeof(buf)) > 0) {
            pdl = mx_request_decode(buf);
        }
        else {
            mx_logger(MX_LOG_FILE, LOGWAR, "mx_recv\n");
        }
    }
    return pdl;
}
