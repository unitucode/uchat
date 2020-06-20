#include "server.h"

static t_dtp *get_resend_msg(t_db_message *msg) {
    cJSON *send_msg = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(send_msg, "type", RQ_MSG))
        return NULL;
    if (!cJSON_AddStringToObject(send_msg, "message", MX_J_STR(msg->message)))
        return NULL;
    if (!cJSON_AddNumberToObject(send_msg, "room_id", msg->room_id))
        return NULL;
    if (!cJSON_AddNumberToObject(send_msg, "date", msg->date))
        return NULL;
    if (!cJSON_AddNumberToObject(send_msg, "message_id", msg->message_id))
        return NULL;
    if (!cJSON_AddNumberToObject(send_msg, "user_id", msg->user_id))
        return NULL;
    // if (!cJSON_AddNumberToObject(send_msg, "status", msg->status))
    //     return NULL;
    return mx_get_transport_data(send_msg);
}

bool mx_msg_handler(t_dtp *data, t_client *client) { // TODO leaks
    // cJSON *msg = cJSON_GetObjectItemCaseSensitive(data->json, "msg");
    // cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json,
    //                                                     "room_id");
    // t_db_message *message = NULL;
    // t_dtp *resend = NULL;

    // if (!msg || !cJSON_IsString(msg))
    //     return false;
    // if (!room_id || !cJSON_IsNumber(room_id))
    //     return false;
    // // message = mx_insert_message_into_db_by_id(client->chat->database,
    //                                     // msg->valuestring, 
    //                                     // (char*)client->user->login,
    //                                     // room_id->valueint);
    // resend = get_resend_msg(message);
    // if (!resend)
    //     return false;
    // mx_send_to_all(resend, client);
    // mx_free_request(&resend);
    t_db_message *msg = mx_parse_message(data->json);
    t_dtp *resend = NULL;

    if (!msg)
        return false; //ADD CONTAINS IN ROOM
    msg->user_id = client->user->user_id;
    mx_insert_message(client->info->database, msg);
    resend = get_resend_msg(msg);
    g_print("send = %s\n", cJSON_Print(resend->json));
    mx_send(client->out, resend); //REPLACE TO SEND TO ALL
    mx_free_request(&resend);
    return true;
}
