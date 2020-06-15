#include "client.h"

char *mx_msgpage_name(int id) {
    char *name = NULL;

    asprintf(&name, "%s_%d", "msgpage_", id);
    return name;
}
