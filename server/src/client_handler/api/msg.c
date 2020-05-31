#include "server.h"

bool mx_msg(t_dtp *data, t_client *client) {
    t_dtp *msg = mx_msg_request(data->str, client->user->login,
                                mx_get_current_time, );

    mx_insert_message(client->chat->database, client->user->login,
                      mx_get_current_time(), data->str);
    
    return true;
}
