#include "api.h"

/*
 * Function: mx_msg_request
 * -------------------------------
 * Creates request "new message"
 * 
 * msg: infomation about message in database
 * 
 * returns: new request
 */
t_dtp *mx_msg_request(t_db_message *msg) {
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
    if (!cJSON_AddNumberToObject(send_msg, "msg_type", msg->type))
        return NULL;
    return mx_get_transport_data(send_msg);
}

static void resend_msg(t_db_message *msg, t_client *client) {
    t_dtp *resend = mx_msg_request(msg);
    mx_send_to_all(resend, client, msg->room_id);
    mx_free_request(&resend);
}

/*
 * Function: mx_msg_handler
 * -------------------------------
 * Handles request from client
 * 
 * data: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
bool mx_msg_handler(t_dtp *data, t_client *client) { // TODO leaks
    t_db_message *msg = mx_parse_message(data->json);

    if (!msg || !strlen(msg->message))
        return false;
    if (!mx_is_member(client->info->database, client->user->user_id,
                      msg->room_id)) {
        mx_free_message(&msg);
        return false;
    }
    if (mx_get_type_member(client->info->database, client->user->user_id,
                           msg->room_id) == DB_BANNED) {
        mx_free_message(&msg);
        return false;
    }
    msg->user_id = client->user->user_id;
    mx_insert_message(client->info->database, msg);
    resend_msg(msg, client);
    return true;
}
