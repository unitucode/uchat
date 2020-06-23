#include "client.h"

gchar *mx_get_string_time(guint64 miliseconds, gint8 format) {
    GDateTime *second = g_date_time_new_from_unix_utc(miliseconds / 1000);

    g_print("\n%s\n", g_date_time_format(second, "%d.%m.%Y    %H:%M:%S"));
    g_print("%s\n\n", g_date_time_format(second, "%H:%M"));
    GDateTime *now = g_date_time_new_now_local();
    if (format == MX_TIME_SHORT)
        return g_date_time_format(now, "%H:%M");
    else
        return g_date_time_format(now, "%d.%m.%Y    %H:%M:%S");
}

