#include "client.h"

void mx_show_user_info(GtkBuilder *builder, gchar *login, gchar *desc) {
    GObject *desc_info = gtk_builder_get_object(builder, "buffer_user_desc");
    GObject *login_info = gtk_builder_get_object(builder,
                                                 "label_user_info_login");

    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(desc_info), desc, -1);
    gtk_label_set_text(GTK_LABEL(login_info), login);
}

t_dtp *mx_member_info_request(int user_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_MEMBER_INFO))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "user_id", user_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_member_info_handler(t_dtp *data, t_chat *chat) {
    cJSON *desc = cJSON_GetObjectItemCaseSensitive(data->json, "desc");
    cJSON *login = cJSON_GetObjectItemCaseSensitive(data->json, "login");

    if (!cJSON_IsString(desc))
        return false;
    if (!cJSON_IsString(login))
        return false;
    g_print("user desc = %s\n, user login = %s\n", desc->valuestring, login->valuestring);
    mx_show_user_info(chat->builder, login->valuestring, desc->valuestring);
    return true;
}
