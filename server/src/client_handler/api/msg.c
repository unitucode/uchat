#include "server.h"

static t_dtp *get_resend_msg(t_db_message *msg) {
    cJSON *send_msg = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(send_msg, "type", RQ_MSG))
        return NULL;
    if (!cJSON_AddStringToObject(send_msg, "msg", MX_J_STR(msg->message)))
        return NULL;
    if (!cJSON_AddStringToObject(send_msg, "room_name", MX_J_STR(msg->name_room)))
        return NULL;
    if (!cJSON_AddNumberToObject(send_msg, "date", msg->date))
        return NULL;
    if (!cJSON_AddStringToObject(send_msg, "login", MX_J_STR(msg->login)))
        return NULL;
    if (!cJSON_AddNumberToObject(send_msg, "id_message", msg->id_message))
        return NULL;
    return mx_get_transport_data(send_msg);
}

bool mx_msg(t_dtp *data, t_client *client) { // TODO leaks
    cJSON *msg = cJSON_GetObjectItemCaseSensitive(data->json, "msg");
    cJSON *room_name = cJSON_GetObjectItemCaseSensitive(data->json,
                                                        "room_name");
    t_db_message *message = NULL;
    t_dtp *resend = NULL;

    if (!msg || !cJSON_IsString(msg))
        return false;
    if (!room_name || !cJSON_IsString(room_name))
        return false;
    message = mx_insert_message_into_db(client->chat->database,
                                        msg->valuestring, 
                                        (char*)client->user->login,
                                        room_name->valuestring);
    resend = get_resend_msg(message);
    if (!resend)
        return false;
    mx_send_to_all(resend, client);
    mx_free_request(&resend);
    return true;
}
