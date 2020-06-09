#include "client.h"

t_groom *mx_get_selected_groom(GtkBuilder *builder) {
    GtkListBox *box = GTK_LIST_BOX(gtk_builder_get_object(builder,
                                                          "listbox_rooms"));
    GObject *row = G_OBJECT(gtk_list_box_get_selected_row(box));
    t_groom *groom = (t_groom*)g_object_get_data(row, "groom");

    return groom;
}
