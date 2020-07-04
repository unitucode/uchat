#include "client.h"

/*
 * Returns groom by id, if not found NULL is returned
 */
t_groom *mx_get_groom_by_id(guint64 room_id, GtkBuilder *builder) {
    GObject *list = gtk_builder_get_object(builder,
                                           "listbox_rooms");
    GtkListBoxRow *row = NULL;
    t_groom *groom = NULL;
    gboolean flag = TRUE;

    for (gint i = 0; flag; i++) {
        row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(list), i);
        if (row == NULL)
            flag = FALSE;
        else {
            groom = (t_groom*)g_object_get_data(G_OBJECT(row), "groom");
            if (room_id == groom->id)
                return groom;
        }
    }
    return NULL;
}

t_groom *mx_get_selected_groom(GtkBuilder *builder, gchar *list_name) {
    GtkListBox *list = GTK_LIST_BOX(gtk_builder_get_object(builder,
                                                           list_name));
    GObject *row = G_OBJECT(gtk_list_box_get_selected_row(list));
    t_groom *groom = NULL;

    if (row)
        groom = (t_groom*)g_object_get_data(row, "groom");
    return groom;
}
