#include "client.h"

gchar *mx_msgpage_name(gint id) {
    gchar *name = NULL;

    asprintf(&name, "%s_%d", "msgpage_", id);
    return name;
}
