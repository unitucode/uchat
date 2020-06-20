#include "server.h"

bool mx_ready_handler(t_dtp *data, t_client *client) {
    puts("ready");
    mx_send(client->out, data);
    return true;
}
