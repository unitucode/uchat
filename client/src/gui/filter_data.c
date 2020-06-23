#include "client.h"

t_filter_data *mx_create_filter_data(gchar *search_name) {
    t_filter_data *filter_data = g_malloc(sizeof(t_filter_data));

    filter_data->search_name = search_name;
    filter_data->is_found_rooms = FALSE;
    return filter_data;
}

void mx_free_filter_data(t_filter_data *filter_data) {
    g_free(filter_data);
}
