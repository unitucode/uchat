#include "utils.h"

/*
 * Wrapper of standart function malloc
 */
void *mx_malloc(size_t size) {
    void *data = malloc(size);

    if (!data) {
        //error
    }
    return data;
}
