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
    if (!cJSON_AddNumberToObject(send_msg, "power", msg->power))
        return NULL;
    return mx_get_transport_data(send_msg);
}

static void update_room_power(t_client *client, guint64 room_id) {
    cJSON *power_json = cJSON_CreateObject();
    gdouble power = mx_get_power_of_room(client->info->database, room_id);
    t_dtp *request = NULL;

    if (!cJSON_AddNumberToObject(power_json, "type", RQ_UPD_ROOM_POWR))
        return;
    if (!cJSON_AddNumberToObject(power_json, "power", power))
        return;
    if (!cJSON_AddNumberToObject(power_json, "room_id", room_id))
        return;
    request = mx_get_transport_data(power_json);
    mx_send_to_all(request, client, room_id);
    mx_free_request(&request);
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
gboolean mx_msg_handler(t_dtp *data, t_client *client) { // TODO leaks
    t_db_message *msg = mx_parse_message(data->json);

    if (!msg || !strlen(msg->message))
        return FALSE;
    if (!mx_is_member(client->info->database, client->user->user_id,
                      msg->room_id)) {
        mx_free_message(&msg);
        return FALSE;
    }
    if (mx_get_type_member(client->info->database, client->user->user_id,
                           msg->room_id) == DB_BANNED) {
        mx_free_message(&msg);
        return FALSE;
    }
    msg->power = mx_get_used_power(data->len);
    msg->user_id = client->user->user_id;
    mx_insert_message(client->info->database, msg);
    resend_msg(msg, client);
    update_room_power(client, msg->room_id);
    return TRUE;
}
