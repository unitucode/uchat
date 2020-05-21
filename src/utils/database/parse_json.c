#include "utils.h"
#include "list.h"
#include "server.h"

static void delete(void **del) {
    free(del);
}

t_dl_list *mx_parse_json(char *rooms_json) {
    t_dl_list *list = mx_new_dl_list(delete);
    cJSON *rooms = cJSON_GetObjectItemCaseSensitive(cJSON_Parse(rooms_json), "rooms");
    int size = cJSON_GetArraySize(rooms);

    for (int i = 0; i < size; i++) {
        cJSON *room_json = cJSON_GetArrayItem(rooms, i);
        t_room_client *room_client = malloc(sizeof(t_room_client));
        t_messages_client *message_client= malloc(sizeof(t_messages_client));
        t_messages_client *save = message_client;
        int size_message = cJSON_GetArraySize(cJSON_GetObjectItemCaseSensitive(room_json, "message"));

        message_client->message = NULL;
        message_client->next = NULL;
        for (int i = 0; i < size_message; i++) {
            cJSON *message = cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(room_json, "message"), i);

            if (message_client->message != NULL) {
                message_client->next = malloc(sizeof(t_messages_client));
                message_client = (t_messages_client*)message_client->next;
            }
            message_client->id_room = cJSON_GetObjectItemCaseSensitive(message, "id_room")->valueint;
            message_client->id_message = cJSON_GetObjectItemCaseSensitive(message, "id_message")->valueint;
            message_client->login = cJSON_GetObjectItemCaseSensitive(message, "login")->valuestring;
            message_client->date = cJSON_GetObjectItemCaseSensitive(message, "date")->valueint;
            message_client->message = cJSON_GetObjectItemCaseSensitive(message, "message")->valuestring;
            message_client->next = NULL;
        }
        room_client->id =  cJSON_GetObjectItemCaseSensitive(room_json, "id_room")->valueint;
        room_client->name = cJSON_GetObjectItemCaseSensitive(room_json, "name_room")->valuestring;
        room_client->customer = cJSON_GetObjectItemCaseSensitive(room_json, "customer_login")->valuestring;
        room_client->data = (void*)save;
        mx_push_front(list, (void*)room_client);
    }
    return list;
}
