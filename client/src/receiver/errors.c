#include "client.h"

bool mx_error_handle(t_dtp *data, t_chat *chat) {
    if (data->type != MX_ERROR_MSG)
        return false;
    chat++; // handle errors
    return true;
}
