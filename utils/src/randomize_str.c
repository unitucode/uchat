#include "utils.h"

void mx_randomize_str(char *str, size_t count) {
    // if (RAND_bytes((unsigned char*)str, count) != 1) {
    //     mx_logger(MX_LOG_FILE, LOGWAR, "RAND_bytes\n");
    // }
    for (size_t i = 0; i < count; i++) {
        str[i] = (char)g_random_int_range(1, CHAR_MAX);
    }
}
