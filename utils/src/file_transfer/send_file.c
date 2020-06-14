#include "protocol.h"
#include "utils.h"

int mx_send_file(SSL *ssl, char *data_bytes, size_t len) {
    size_t written = 0;
    char *data = data_bytes;
    long int bytes = MX_RQ_SIZE;

    while (written < len) {
        if (len - written < MX_RQ_SIZE)
            bytes = len - written;
        if (SSL_write(ssl, data + written, bytes) <= 0) {
            mx_logger(MX_LOG_FILE, LOGWAR, "SSL_write data failed\n");
            return false;
        }
        written += bytes;
        fprintf(stderr, "written = %zu\n", written);
        usleep(50000);
    }
    return true;
}
