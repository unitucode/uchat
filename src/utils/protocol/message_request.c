#include "protocol.h"

t_dtp *mx_msg_request(int id_room, char *from, char *msg) {
    t_dtp *dtp = mx_request_json("{\"type\": %d, \"id_room\": %d, \
    \"from\": \"%s\", \"msg\": \"%s\"}", MX_MSG, id_room, from, msg);

    return dtp;
}
