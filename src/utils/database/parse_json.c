#include "utils.h"

// static t_node *get_room_data(cJSON *room) {
//     t_room_data *room_data = malloc(sizeof(t_room_data));
//     cJSON *message = cJSON_GetObjectItemCaseSensitive(room, "message");
//     int size = cJSON_GetArraySize(message);

//     room_data->id = cJSON_GetObjectItemCaseSensitive(room, "id")->valueint;
//     room_data->name = cJSON_GetObjectItemCaseSensitive(room, "name" )->valuestring;
//     room_data->customer = cJSON_GetObjectItemCaseSensitive(room, "customer")->valuestring;
//     for (int i = 0; i < size; i++) {
//         t_room_message *object_message = 
//     }
//     return room_data;
// }

void mx_parse_j() {

}

// void mx_parse_json(char *rooms_json) {
//     t_list *list = malloc(sizeof(t_list));
//     cJSON *rooms;
//     t_node *node = malloc(sizeof(t_node));

//     list->head = node;
//     rooms = cJSON_GetObjectItemCaseSensitive(cJSON_Parse(rooms_json), "rooms" );
//     list->size = cJSON_GetArraySize(rooms);
//     for (int i = 0; i < (int)list->size; i++) {
//         t_node *new_node = get_room_data(cJSON_GetArrayItem(rooms, i));
        
    // }   
// }
