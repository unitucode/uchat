#include "server.h"

guint64 mx_get_time(gint8 type) {
    guint64 date = g_get_real_time();
    guint64 time;

    date += (3 * 60 * 60 * 100 * 100);
    if (type == DB_SECOND)
        time = date / 1000000;
    else if (type == DB_MILISECOND)
        time = date / 1000;
    else
        time = date;
    return time;
}

