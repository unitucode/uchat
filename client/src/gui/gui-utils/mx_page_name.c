#include "client.h"

char *mx_page_name(int id) {
    char *name = NULL;

    asprintf(&name, "%s_%d", "msgpage_", id);
    return name;
}
