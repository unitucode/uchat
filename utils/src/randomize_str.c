#include "utils.h"

void mx_randomize_str(char *str, size_t count) {
    for (size_t i = 0; i < count; i++) {
        str[i] = (char)g_random_int_range(1, CHAR_MAX);
    }
}
