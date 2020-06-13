#include "client.h"

void mx_gupd_room_desc(int id, char *desc, GtkBuilder *builder) {
    t_groom *groom = mx_get_groom_by_id(id, builder);

    mx_free((void **)&(groom->desc));
    groom->desc = strdup(desc);
    mx_set_current_room_sett(builder);
}

void mx_gupd_room_name(int id, char *name, GtkBuilder *builder) {
    t_groom *groom = mx_get_groom_by_id(id, builder);

    mx_free((void**)&(groom->room_name));
    groom->room_name = strdup(name);
    gtk_label_set_text(groom->label_name, groom->room_name);
    mx_set_current_room_sett(builder);
}

void mx_gdel_room(int id, GtkBuilder *builder) {
    t_groom *groom = mx_get_groom_by_id(id, builder);
    GObject *room_sett = gtk_builder_get_object(builder, "dialog_room_sett");

    mx_delete_row_room(groom->row_room, builder);
    mx_widget_switch_visibility(NULL, GTK_WIDGET(room_sett));
}
