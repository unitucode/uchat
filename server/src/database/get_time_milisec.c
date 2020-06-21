#include "server.h"

guint64 mx_get_time(gint8 type) {
    struct timeval time;
    guint64 date;

    gettimeofday(&time, 0);
    if (type == DB_SECOND)
        date = time.tv_sec;
    if (type == DB_MILISECOND)
        date = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    if (type == DB_MICROSECOND)
        date = time.tv_sec * 1000000 + time.tv_usec;
    return date;
}
