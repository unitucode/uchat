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
        mx_logger(MX_LOG_FILE, LOGWAR, "Invalid packet. Readed %d\n", bytes);
        return -1;
    }
    memcpy(&size, buf, sizeof(int));
    return size;
}

/*
 * Receive message from ssl socket
 */
t_dtp *mx_recv(SSL *ssl) {
    t_dtp *dtp = NULL;
    int size = 0;
    long int bytes = MX_RQ_SIZE;
    long int read = 0;

    if ((size = message_size(ssl)) > 0) {
        char data[size + 1];

        bzero(data, sizeof(data));
        if (size < MX_RQ_SIZE)
            bytes = size;
        while (read < size && SSL_read(ssl, &data[read], bytes) > 0) {
            read += bytes;
            if (size - read < MX_RQ_SIZE)
                bytes = size - read;
        }
        if (read == size)
            dtp = mx_request_creation(data);
        else
            mx_logger(MX_LOG_FILE, LOGWAR, "Invalid len of packet\n");
    }
    return dtp;
}
