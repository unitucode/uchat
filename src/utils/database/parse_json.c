#include "utils.h"
#include "list.h"
#include "server.h"

static t_messages *write_message(t_messages *msg_cl,
                                       t_messages *save, 
                                       cJSON *room_json, int size_message) {
    for (int i = 0; i < size_message; i++) {
        cJSON *ms = cJSON_GetArrayItem(
            cJSON_GetObjectItemCaseSensitive(room_json, "message"), i);

        if (msg_cl->message != NULL) {
            msg_cl->next = malloc(sizeof(t_messages));
            msg_cl = (t_messages*)msg_cl->next;
        }
        msg_cl->id_room = 
        cJSON_GetObjectItemCaseSensitive(ms, "id_room")->valueint;
        msg_cl->id_message = 
        cJSON_GetObjectItemCaseSensitive(ms, "id_message")->valueint;
        msg_cl->login = 
        cJSON_GetObjectItemCaseSensitive(ms, "login")->valuestring;
        msg_cl->date = cJSON_GetObjectItemCaseSensitive(ms, "date")->valueint;
        msg_cl->message = 
        cJSON_GetObjectItemCaseSensitive(ms, "message")->valuestring;
        msg_cl->next = NULL;
    }
    return save;
}

static void write_one_node_to_list(cJSON *rooms, t_dl_list *list, int i) {
    cJSON *room_json = cJSON_GetArrayItem(rooms, i);
    t_room *room = malloc(sizeof(t_room));
    t_messages *msg_cl= malloc(sizeof(t_messages));
    t_messages *save = msg_cl;
    int size_message = 
    cJSON_GetArraySize(cJSON_GetObjectItemCaseSensitive(room_json, "message"));

    msg_cl->message = NULL;
    msg_cl->next = NULL;
    room->id =   
    cJSON_GetObjectItemCaseSensitive(room_json, "id_room")->valueint;
    room->name = 
    cJSON_GetObjectItemCaseSensitive(room_json, "name_room")->valuestring;
    room->customer = 
    cJSON_GetObjectItemCaseSensitive(room_json, "customer_login")->valuestring;
    room->data = (void*)write_message(msg_cl, save,
                                             room_json, size_message);
    mx_push_front(list, (void*)room);
}

static void delete(void **del) {
    free(del);
}

t_dl_list *mx_parse_json(char *rooms_json) {
    t_dl_list *list = mx_new_dl_list(delete);
    cJSON *rooms = 
    cJSON_GetObjectItemCaseSensitive(cJSON_Parse(rooms_json), "rooms");
    int size = cJSON_GetArraySize(rooms);

    for (int i = 0; i < size; i++)
        write_one_node_to_list(rooms, list, i);
    return list;
}

void mx_parse_message(cJSON *room_mss, t_dl_list *list) {
    t_node *front = list->front;
    int id_room = 
        cJSON_GetObjectItemCaseSensitive(room_mss, "id_room")->valueint;

    while (front != NULL) {
        t_room *room = (t_room*)(front->data);

        if (room->id == (unsigned int)id_room) {
            t_messages *messages = (t_messages*)(room->data);
            t_messages *save = messages;
            int size_message = cJSON_GetArraySize(
                cJSON_GetObjectItemCaseSensitive(room_mss, "message"));
            while (messages->next != NULL)
                messages = messages->next;
            write_message(messages, save, room_mss, size_message);
            break;
        }
        front = front->next;
    }
}
