#include "client.h"

gchar *mx_msgpage_name(gint id) {
    return g_strdup_printf("%s_%d", "msgpage_", id);
}
