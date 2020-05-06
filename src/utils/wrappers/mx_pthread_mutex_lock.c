#include "utils.h"

int mx_pthread_mutex_lock(pthread_mutex_t *mutex) {
    int result = pthread_mutex_lock(mutex);

    if (result)
        mx_elogger(MX_LOG_FILE, LOGERR, "pthread_mutex_lock\n");
    return result;
}
