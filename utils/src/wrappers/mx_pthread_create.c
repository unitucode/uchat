#include "utils.h"

/*
 * Wrapper of standart function pthread_create
 */
int mx_pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg) {
    int result = pthread_create(thread, attr, start_routine, arg);

    if (result) {
        errno = result;
        mx_elogger(MX_LOG_FILE, LOGERR, "pthread_create\n");
    }
    return result;
}
