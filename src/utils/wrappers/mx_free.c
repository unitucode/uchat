#include "utils.h"

/*
 * Wrapper of standart function free
 */
void mx_free(void **ptr) {
    if (ptr && *ptr) {
        free(*ptr);
        *ptr = NULL;
    }
}
