#include "server.h"

void mx_resend_msg(t_message *msg) {
    
}

bool mx_msg(t_dtp *data, t_client *client) {
    cJSON *msg = cJSON_GetObjectItemCaseSensitive(data->json, "msg");
    cJSON *room_name = cJSON_GetObjectItemCaseSensitive(data->json,
                                                        "room_name");
    t_message *message = NULL;

    if (!cJSON_IsString(msg))
        return false;
    if (!cJSON_IsString(room_name))
        return false;
    message = mx_insert_message_into_db(client->chat->database,
                                        msg->valuestring, client->user->login,
                                        room_name->valuestring);
    
    return true;
}
