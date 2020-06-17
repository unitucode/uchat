#include "client.h"

void mx_select_msg(gpointer *eventbox, gpointer *event, t_signal_data *data) {
    t_groom *groom = mx_get_selected_groom(data->builder);

    if (!mx_widget_is_visible("box_editing_msg", data->builder)) {
        if (gtk_list_box_row_is_selected(GTK_LIST_BOX_ROW(data->row_msg))) {
            mx_switch_room_header(data->builder, MX_ROOM_CTRL);
            gtk_list_box_unselect_row(GTK_LIST_BOX(groom->box_messages),
                                    GTK_LIST_BOX_ROW(data->row_msg));
            gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(data->row_msg), FALSE);

        }
        else {
            mx_switch_room_header(data->builder, MX_MSG_CTRL);
            gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(data->row_msg), TRUE);
            gtk_list_box_select_row(GTK_LIST_BOX(groom->box_messages),
                                    GTK_LIST_BOX_ROW(data->row_msg));
        }
    }
    (void)eventbox;
    (void)event;
}
