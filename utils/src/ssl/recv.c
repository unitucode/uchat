#include "protocol.h"

/*
 * Receive first packet with size of next packet
 */
static int message_size(SSL *ssl) {
    char buf[sizeof(int)];
    int bytes = 0;
    int size = -1;

    bytes = SSL_read(ssl, buf, sizeof(buf));
    if (bytes != sizeof(int)) {
        mx_logger(MX_LOG_FILE, LOGWAR, "Invalid packet\n");
        return -1;
    }
    memcpy(&size, buf, sizeof(int));
    return size;
}

/*
 * Receive message from ssl socket
 */
t_dtp *mx_recv(SSL *ssl) {
    // t_dtp *dtp = NULL;
    // int size = 0;
    // int bytes = 0;

    // if ((size = message_size(ssl)) > 0) {
    //     char buf[size + 1];

    //     if ((bytes = SSL_read(ssl, buf, size)) == size) {
    //         buf[bytes] = '\0';
    //         dtp = mx_request_creation(buf);
    //     }
    //     else
    //         mx_logger(MX_LOG_FILE, LOGWAR, "mx_recv\n");
    // }
    // return dtp;

    t_dtp *dtp = NULL;
    int size = 0;
    int bytes = 0;
    int readed_bytes = 0;

    if ((size = message_size(ssl)) > 0) {
        char data[size + 1];
        char buf[MX_RQ_SIZE + 1];

        bzero(data, sizeof(data));
        bzero(buf, sizeof(buf));
        while ((bytes = SSL_pending(ssl)) > 0) {
            if ((SSL_read(ssl, buf, bytes > MX_RQ_SIZE ? MX_RQ_SIZE : bytes)) <= 0) {
                mx_logger(MX_LOG_FILE, LOGWAR, "mx_recv\n");
                break;
            }
            readed_bytes += bytes;
            strcat(data, buf);
            bzero(buf, sizeof(buf));
        }
        printf("strlen = %ld size = %d\n", strlen(data), size);
        if (strlen(data) == (unsigned int)size) {
            printf("data = %s\n", data);
            dtp = mx_request_creation(data);
        }
    }
    if (!dtp)
        puts("NULL");
    return dtp;
}
