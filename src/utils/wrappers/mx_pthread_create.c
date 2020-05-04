#include "utils.h"

int mx_pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg) {
    int n;

    if ((n = pthread_create(thread, attr, start_routine, arg)) == 0) {
        return n;
    }
    errno = n;
    //error 
    return n;
}
