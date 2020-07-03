#include "client.h"

void mx_unselect_room(t_groom *groom, GtkBuilder *builder) {
    mx_set_default_room_sett(builder);
    if (groom->page)
        gtk_widget_hide(GTK_WIDGET(groom->page));
    if (groom->row_room)
        gtk_widget_hide(GTK_WIDGET(groom->row_room));
    mx_set_room_widgets_visibility(builder, FALSE);
}

void mx_delete_row_room(GtkListBoxRow *row, GtkBuilder *builder) {
    t_groom *groom = g_object_get_data(G_OBJECT(row), "groom");

    if (gtk_list_box_row_is_selected(row))
        mx_unselect_room(groom, builder);
    if (groom->page)
        gtk_widget_destroy(GTK_WIDGET(groom->page));
    gtk_widget_destroy(GTK_WIDGET(row));
}
