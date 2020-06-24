#include "client.h"

gchar *mx_get_string_time(guint64 miliseconds, gint8 format) {
    GDateTime *dt = g_date_time_new_from_unix_utc(miliseconds / 1000);
    GDateTime *new = g_date_time_to_local(dt);

    if (format == MX_TIME_SHORT)
        return g_date_time_format(new, "%H:%M");
    else
        return g_date_time_format(new, "%d.%m.%Y    %H:%M:%S");
}

