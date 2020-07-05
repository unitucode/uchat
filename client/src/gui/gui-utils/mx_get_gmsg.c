#include "client.h"

t_gmsg *mx_get_selected_gmsg(GtkBuilder *builder) {
    t_groom *room = mx_get_selected_groom(builder, MX_LOCAL_ROOMS);
    GObject *row = NULL;
    t_gmsg *gmsg = NULL;

    if (room->select_all == 1)
        row = gtk_list_box_get_selected_rows(room->box_messages)->data;
    if (row)
        gmsg = (t_gmsg*)g_object_get_data(row, "gmsg");
    return gmsg;
}
