#include "server.h"

/*
 * Function: mx_json_is_valid
 * -------------------------------
 * checks whether the value matches its type
 * 
 * date: json object
 * str: the key value to be checked
 * check_valid: function to check
 * 
 * return json object if all ok else NULL
 */
cJSON *mx_json_is_valid(cJSON *data, gchar *str, 
                        cJSON_bool(check_valid)(const cJSON * const)) {
    cJSON *json = cJSON_GetObjectItemCaseSensitive(data, str);

    if (!json || !check_valid(json))
        return NULL;
    return json;
}

/*
 * Function: mx_parse_json_user
 * -------------------------------
 * writes data from the json object to the structure t_db_user
 * 
 * user_j: json object
 * 
 * return: filled structure t_db_user if all is well otherwise NULL
 */
t_db_user *mx_parse_json_user(cJSON *user_j) {
    t_db_user *user = malloc(sizeof(t_db_user));
    cJSON *json = NULL;

    if (!(json = mx_json_is_valid(user_j, "name", cJSON_IsString)))
        return NULL;
    user->name = strdup(json->valuestring);
    if (!(json = mx_json_is_valid(user_j, "login", cJSON_IsString)))
        return NULL;
    user->login = strdup(json->valuestring);
    if (!(json = mx_json_is_valid(user_j, "desc", cJSON_IsString)))
        return NULL;
    user->desc = strdup(json->valuestring);
    if (!(json = mx_json_is_valid(user_j, "pass", cJSON_IsString)))
        return NULL;
    user->pass = strdup(json->valuestring);
    user->token = NULL;
    return user;
}

/*
 * Function: mx_parse_json_room
 * -------------------------------
 * writes data from the json object to the structure t_db_room
 * 
 * room_j: json object
 * 
 * return: filled structure t_db_room if all is well otherwise NULL
 */
t_db_room *mx_parse_json_room(cJSON *room_j) {
    t_db_room *room = malloc(sizeof(t_db_room));
    cJSON *json = NULL;

    if (!(json = mx_json_is_valid(room_j, "name", cJSON_IsString)))
        return NULL;
    room->room_name = strdup(json->valuestring);
    if (!(json = mx_json_is_valid(room_j, "desc", cJSON_IsString)))
        return NULL;
    room->desc = strdup(json->valuestring);
    if (!(json = mx_json_is_valid(room_j, "type", cJSON_IsNumber)))
        return NULL;
    room->type = json->valueint;
    room->power = 0;
    return room;
}

/*
 * Function: mx_parse_json_message
 * -------------------------------
 * writes data from the json object to the structure t_db_message
 * 
 * message_j: json object
 * 
 * return: filled structure t_db_message if all is well otherwise NULL
 */
t_db_message *mx_parse_message(cJSON *message_j) {
    t_db_message *message = malloc(sizeof(t_db_message));
    cJSON *json = NULL;

    if (!(json = mx_json_is_valid(message_j, "room_id", cJSON_IsNumber)))
        return NULL;
    message->room_id = json->valueint;
    if (!(json = mx_json_is_valid(message_j, "msg_type", cJSON_IsNumber)))
        return NULL;
    message->type = json->valueint;
    message->file_size = 0;
    if (!(json = mx_json_is_valid(message_j, "message", cJSON_IsString)))
        return NULL;
    message->message = g_strstrip(g_strdup(json->valuestring));
    message->file_name = g_strdup("");
    return message;
}

