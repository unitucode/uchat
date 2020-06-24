#include "server.h"

guint64 mx_get_time(gint8 type) {
    gint64 dt = 0;
    GDateTime *gtime = g_date_time_new_now_local();

    dt = g_date_time_to_unix(gtime);
    dt *= 1000000;
    dt += g_date_time_get_microsecond(gtime);
    if (type == DB_SECOND)
        dt /= 1000000;
    else if (type == DB_MILISECOND)
        dt /= 1000;
    return dt;
}

