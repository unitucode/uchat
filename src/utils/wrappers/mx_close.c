#include "utils.h"

/*
 * Wrapper of standart function close
 */
int mx_close(int fd) {
    int result = close(fd);
    
    if (result == -1) {
        //error
    }
    return result;
}
