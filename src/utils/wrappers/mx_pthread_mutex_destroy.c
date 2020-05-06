#include "utils.h"

/*
 * Wrapper of standart function pthread_mutex_destroy
 */
int mx_pthread_mutex_destroy(pthread_mutex_t *mutex) {
    int result = pthread_mutex_destroy(mutex);

    if (result) {
        //error
    }
    return result;
}
