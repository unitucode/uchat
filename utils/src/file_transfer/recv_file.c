#include "protocol.h"
#include "utils.h"

char *mx_recv_file(SSL *ssl, size_t size) {
    long int bytes = MX_RQ_SIZE;
    size_t read = 0;
    char *data = mx_malloc(size + 1);

    bzero(data, size + 1);
    if (size < MX_RQ_SIZE)
        bytes = size;
    while (read < size && SSL_read(ssl, &data[read], bytes) > 0) {
        read += bytes;
        if (size - read < MX_RQ_SIZE)
            bytes = size - read;
        fprintf(stderr, "read = %zu\n", read);
    }
    if (read == size)
        return data;
    else
        mx_logger(MX_LOG_FILE, LOGWAR, "Invalid len of packet\n");
    mx_free((void**)&data);
    return NULL;
}
