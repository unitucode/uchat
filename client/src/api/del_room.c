#include "client.h"

static void gdel_room(int id, GtkBuilder *builder) {
    t_groom *groom = mx_get_groom_by_id(id, builder);
    GObject *room_sett = gtk_builder_get_object(builder, "dialog_room_sett");

    mx_delete_row_room(groom->row_room, builder);
    mx_widget_switch_visibility(NULL, GTK_WIDGET(room_sett));
}

t_dtp *mx_del_room_request(int room_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_DEL_ROOM))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_del_room_handler(t_dtp *data, t_chat *chat) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");

    if (!room_id || !cJSON_IsNumber(room_id))
        return false;
    gdel_room(room_id->valueint, chat->builder);
    return true;
}
