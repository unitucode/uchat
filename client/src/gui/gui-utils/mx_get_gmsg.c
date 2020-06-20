#include "client.h"

t_gmsg *mx_get_selected_gmsg(GtkBuilder *builder) {
    t_groom *room = mx_get_selected_groom(builder);
    GObject *row = G_OBJECT(gtk_list_box_get_selected_row(room->box_messages));
    t_gmsg *gmsg = NULL;

    if (row)
        gmsg = (t_gmsg*)g_object_get_data(row, "gmsg");
    return gmsg;
}
