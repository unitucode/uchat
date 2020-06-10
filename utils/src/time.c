#include "utils.h"

long long mx_get_current_time(void) {
    time_t t = time(NULL);

    return t;
}
