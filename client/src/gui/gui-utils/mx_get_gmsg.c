#include "client.h"

t_gmsg *mx_get_selected_gmsg(GtkBuilder *builder) {
    t_groom *room = mx_get_selected_groom(builder, MX_LOCAL_ROOMS);
    GObject *row = G_OBJECT(gtk_list_box_get_selected_row(room->box_messages));
    t_gmsg *gmsg = NULL;

    if (row)
        gmsg = (t_gmsg*)g_object_get_data(row, "gmsg");
    if (gtk_list_box_row_is_selected(gmsg->row_msg))
        return gmsg;
    return NULL;
}
