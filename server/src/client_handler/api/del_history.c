#include "api.h"

/*
 * Function: mx_del_hist_request
 * -------------------------------
 * Creates request "delete history"
 * 
 * room_id: room id thath need to clear
 * 
 * returns: new request
 */
t_dtp *mx_del_hist_request(guint64 room_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_DEL_HIST))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

/*
 * Function: mx_del_hist_handler
 * -------------------------------
 * Handles request from client
 * 
 * msg: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_del_hist_handler(t_dtp *msg, t_client *client) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(msg->json, "room_id");
    t_dtp *resend = NULL;

    if (!cJSON_IsNumber(room_id))
        return FALSE;
    if (!mx_is_member(client->info->database, client->user->user_id,
                      room_id->valueint)) {
        return FALSE;
    }
    if (mx_get_type_member(client->info->database, client->user->user_id,
                           room_id->valueint) != DB_CUSTOMER) {
        return FALSE;
    }
    mx_delete_all_messages(client->info->database, room_id->valueint);
    resend = mx_del_hist_request(room_id->valueint);
    mx_send_to_all(resend, client, room_id->valueint);
    mx_free_request(&resend);
    return TRUE;
}
