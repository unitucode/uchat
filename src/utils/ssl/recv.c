#include "utils.h"

/*
 * Receive first packet with size of next packet
 */
static int message_size(SSL *ssl) {
    t_pdl *pdl = NULL;
    char buf[MX_BUF_SIZE];
    size_t bytes = 0;
    int size = -1;

    while ((bytes = SSL_read(ssl, buf, sizeof(buf))) > 0) {
        buf[bytes] = '\0';
        pdl = mx_request_decode(buf);
        if (pdl && pdl->type == MX_SIZE_MSG) {
            size = atoi(pdl->data);
            break;
        }
        else {
            mx_logger(MX_LOG_FILE, LOGWAR, "First message wasn`t size\n");
        }
        mx_free_decode_struct(&pdl);
    }
    if (pdl)
        mx_free_decode_struct(&pdl);
    return size;
}

/*
 * Receive message from ssl socket
 */
t_pdl *mx_recv(SSL *ssl) {
    t_pdl *pdl = NULL;
    int size = 0;
    int bytes = 0;

    if ((size = message_size(ssl)) > 0) {
        char buf[size];

        buf[size] = '\0';
        if ((bytes = SSL_read(ssl, buf, sizeof(buf))) == size)
            pdl = mx_request_decode(buf);
        else
            mx_logger(MX_LOG_FILE, LOGWAR, "mx_recv\n");
    }
    return pdl;
}
