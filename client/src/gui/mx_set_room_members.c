#include "client.h"

static void reset_room_members(GObject *listbox_sett, GObject *listbox_info,
                               GtkListBoxRow *sett, GtkListBoxRow *info) {
    sett = gtk_list_box_get_row_at_index(GTK_LIST_BOX(listbox_sett), 0);
    info = gtk_list_box_get_row_at_index(GTK_LIST_BOX(listbox_info), 0);
    while (sett) {
        gtk_widget_destroy(GTK_WIDGET(sett));
        sett = gtk_list_box_get_row_at_index(GTK_LIST_BOX(listbox_sett), 0);
    }
    while (info) {
        gtk_widget_destroy(GTK_WIDGET(info));
        info = gtk_list_box_get_row_at_index(GTK_LIST_BOX(listbox_info), 0);
    }
}

void mx_set_room_members(GtkBuilder *builder, t_groom *groom) {
    GObject *listbox_sett = gtk_builder_get_object(builder,
                                                   "listbox_sett_members");
    GObject *listbox_info = gtk_builder_get_object(builder,
                                                   "listbox_info_members");
    GtkListBoxRow *row_sett = NULL;
    GtkListBoxRow *row_info = NULL;

    reset_room_members(listbox_sett, listbox_info, row_sett, row_info);
    g_hash_table_foreach(groom->members,
                        (GHFunc)mx_add_to_sett_members, builder);
    g_hash_table_foreach(groom->members,
                        (GHFunc)mx_add_to_info_members, builder);
}
