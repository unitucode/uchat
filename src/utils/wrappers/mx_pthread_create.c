#include "utils.h"

int mx_pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg) {
    int n = pthread_create(thread, attr, start_routine, arg);

    if (n) {
        errno = n;
        mx_elogger(MX_LOG_FILE, LOGERR, "pthread_create\n");
    }
    return n;
}
