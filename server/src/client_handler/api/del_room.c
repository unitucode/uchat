#include "api.h"

/*
 * Function: mx_del_room_request
 * -------------------------------
 * Creates request "delete room"
 * 
 * room_id: room id thath need to delete
 * 
 * returns: new request
 */
t_dtp *mx_delete_room_request(guint64 room_id) {
    cJSON *send = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(send, "type", RQ_DEL_ROOM))
        return NULL;
    if (!cJSON_AddNumberToObject(send, "room_id", room_id))
        return NULL;
    return mx_get_transport_data(send);
}

/*
 * Function: mx_del_room_handler
 * -------------------------------
 * Handles request from client
 * 
 * data: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_del_room_handler(t_dtp *data, t_client *client) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json,
                                                      "room_id");
    t_dtp *resend = NULL;

    if (!cJSON_IsNumber(room_id))
        return FALSE;
    if (mx_get_type_member(client->info->database, client->user->user_id,
                           room_id->valueint) != DB_CUSTOMER) {
        return FALSE;
    }
    resend = mx_delete_room_request(room_id->valueint);
    mx_send_to_all(resend, client, room_id->valueint);
    mx_delete_room_by_id(client->info->database, room_id->valueint);
    mx_free_request(&resend);
    return TRUE;
}
