#include "server.h"

guint64 mx_get_time(gint8 type) {
    guint64 date = g_get_real_time();

    if (type == DB_SECOND)
        return date / 10000000;
    if (type == DB_MILISECOND)
        return date / 1000;
    return date;
}

