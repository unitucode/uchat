#include "client.h"

void mx_gupd_clear_history(GtkBuilder *builder, gint room_id) {
    t_groom *groom = mx_get_groom_by_id(room_id, builder);
    GtkListBoxRow *row = gtk_list_box_get_row_at_index(groom->box_messages, 0);

    while (row) {
        gtk_widget_destroy(GTK_WIDGET(row));
        row = gtk_list_box_get_row_at_index(groom->box_messages, 0);
        groom->uploaded--;
    }
}
