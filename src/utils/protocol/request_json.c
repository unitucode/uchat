#include "protocol.h"

t_dtp *mx_request_json(const char *fmt, ...) {
    va_list ap;
    char *request = NULL;
    t_dtp *dtp = NULL;

    va_start(ap, fmt);
    vasprintf(&request, fmt, ap);
    dtp = mx_request_creation(request);
    mx_free((void**)&request);
    va_end(ap);
    return dtp;
}
