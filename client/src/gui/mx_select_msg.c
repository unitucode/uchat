#include "client.h"

void mx_select_msg(gpointer *eventbox, gpointer *event, t_signal_data *data) {
    t_groom *groom = mx_get_selected_groom(data->builder,  MX_LOCAL_ROOMS);
    GList *rows = NULL;

    if (!mx_widget_is_visible("box_editing_msg", data->builder)) {
        if (gtk_list_box_row_is_selected(GTK_LIST_BOX_ROW(data->row_msg))) {
            gtk_list_box_unselect_row(GTK_LIST_BOX(groom->box_messages),
                                    GTK_LIST_BOX_ROW(data->row_msg));
            rows = gtk_list_box_get_selected_rows(groom->box_messages);
            if (!rows)
                mx_switch_room_header(data->builder, MX_ROOM_CTRL);
        }
        else {
            gtk_list_box_select_row(GTK_LIST_BOX(groom->box_messages),
                                    GTK_LIST_BOX_ROW(data->row_msg));
            mx_switch_room_header(data->builder, MX_MSG_CTRL);
            rows = gtk_list_box_get_selected_rows(groom->box_messages);
        }
    }
    if (g_list_length(rows) <= 1)
        mx_widget_set_visibility_by_name(data->builder, "btn_edit_msg", TRUE);
    else
        mx_widget_set_visibility_by_name(data->builder, "btn_edit_msg", FALSE);
    g_list_free(rows);
    (void)eventbox;
    (void)event;
}
