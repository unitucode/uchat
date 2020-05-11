#include "utils.h"

/*
 * Creates md5 hash from str
 */
void mx_md5(char *buf, const unsigned char *str, size_t len) {
    unsigned char md5digest[MD5_DIGEST_LENGTH];
    char byte_buf[3];

    bzero(byte_buf, 3);
    bzero(buf, MX_MD5_BUF_SIZE + 1);
    MD5(str, len, md5digest);
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(byte_buf, "%02x", md5digest[i]);
        strcat(buf, byte_buf);
    }
}
