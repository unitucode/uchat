#include "server.h"

long long mx_get_time() {
    struct timeval time;
    long milisec;

    gettimeofday(&time, 0);
    milisec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    fprintf(stderr, " -> -> -> %ld\n", milisec);
    return milisec;
}
