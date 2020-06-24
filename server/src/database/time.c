#include "server.h"

guint64 mx_get_time(gint8 type) {
    gint64 dt = 0;
    GDateTime *gtime = g_date_time_new_now_local();

    dt += (31556926 * (g_date_time_get_year(gtime) - 1970));
    dt += (86400 * g_date_time_get_day_of_year(gtime));
    dt += (3600 * g_date_time_get_hour(gtime));
    dt += (60 * g_date_time_get_minute(gtime));
    dt += g_date_time_get_second(gtime);
    dt *= 1000000;
    dt += g_date_time_get_microsecond(gtime);
    if (type == DB_SECOND)
        dt /= 1000000;
    else if (type == DB_MILISECOND)
        dt /= 1000;
    return dt;
}

