#include "utils.h"

/*
 * Wrapper of standart function pthread_mutex_init
 */
int mx_pthread_mutex_init(pthread_mutex_t *mutex,
                          const pthread_mutexattr_t *attr) {
    int result = pthread_mutex_init(mutex, attr);

    if (result) {
        //error
    }
    return result;
}
