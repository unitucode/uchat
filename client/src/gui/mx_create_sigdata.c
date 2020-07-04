#include "client.h"

t_signal_data *mx_create_sigdata(t_chat *chat, t_groom *groom,
                                 GtkListBoxRow *row_msg) {
    t_signal_data *data = malloc(sizeof(t_signal_data));

    data->chat = chat;
    data->groom = groom;
    data->row_msg = row_msg;
    return data;
}

void mx_free_sigdata(t_signal_data *data) {
    mx_free((void **)&data);
}
