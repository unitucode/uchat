#include "utils.h"

int mx_pthread_mutex_unlock(pthread_mutex_t *mutex) {
    int result = pthread_mutex_unlock(mutex);

    if (result)
        mx_elogger(MX_LOG_FILE, LOGERR, "pthread_mutex_unlock\n");
    return result;
}
