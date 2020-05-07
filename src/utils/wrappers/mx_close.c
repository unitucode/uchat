#include "utils.h"

/*
 * Wrapper of standart function close
 */
int mx_close(int fd) {
    int result = close(fd);
    
    if (result == -1)
        mx_elogger(MX_LOG_FILE, LOGERR, "close\n");
    return result;
}
