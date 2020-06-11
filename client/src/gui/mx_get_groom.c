#include "client.h"

/*
 * Returns groom by name, if not found NULL is returned
 */
t_groom *mx_get_groom_by_name(char *name, GtkBuilder *builder) {
    GObject *list = gtk_builder_get_object(builder,
                                           "listbox_rooms");
    GtkListBoxRow *row = NULL;
    t_groom *groom = NULL;
    bool flag = true;

    for (int i = 0; flag; i++) {
        row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(list), i);
        if (row == NULL)
            flag = false;
        else {
            groom = (t_groom*)g_object_get_data(G_OBJECT(row), "groom");
            if (!strcmp(name, groom->room_name))
                return groom;
        }
    }
    return NULL;
}

t_groom *mx_get_selected_groom(GtkBuilder *builder) {
    t_groom *groom = NULL;
    GtkListBox *list = GTK_LIST_BOX(gtk_builder_get_object(builder,
                                                           "listbox_rooms"));
    GObject *row = G_OBJECT(gtk_list_box_get_selected_row(list));

    if  (row)
        groom = (t_groom*)g_object_get_data(row, "groom");
    return groom;
}
