#include "client.h"

static gboolean filter_room_name(GtkListBoxRow *row,
                                 t_filter_data *data) {
    t_groom *groom = (t_groom*)g_object_get_data(G_OBJECT(row), "groom");
    char *room_name = (char*)gtk_label_get_text(groom->label_name);

    if (!strncasecmp(room_name, data->search_name,
                     strlen(data->search_name))) {
        data->is_found_rooms = TRUE;
        return TRUE;
    }
    else {
        data->is_found_rooms = (data->is_found_rooms || FALSE);
        return FALSE;
    }
}

void mx_search_delim_set_visibility(GtkBuilder *builder,
                                    gboolean is_visible) {
    mx_widget_set_visibility_by_name(builder,
                                     "label_search_delim_global", is_visible);
    mx_widget_set_visibility_by_name(builder,
                                     "label_search_delim_local", is_visible);
}

void mx_search_local_rooms(GtkBuilder *builder, t_filter_data *data) {
    GObject *listbox = gtk_builder_get_object(builder, "listbox_rooms");

    gtk_list_box_set_filter_func(GTK_LIST_BOX(listbox),
                                (GtkListBoxFilterFunc)filter_room_name,
                                data, NULL);
    if (!data->is_found_rooms) {
        mx_widget_set_visibility_by_name(builder, 
                                         "label_search_nothing_local", TRUE);
    }
    else {
        mx_widget_set_visibility_by_name(builder, 
                                         "label_search_nothing_local", FALSE);
    }
}

void mx_clear_global_search(GtkBuilder *builder) {
    GObject *box = (gtk_builder_get_object(builder, "listbox_global_rooms"));
    GtkListBoxRow *row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(box), 0);

    mx_widget_set_visibility_by_name(builder,
                                     "label_search_nothing_global", FALSE);
    while (row) {
        mx_delete_row_room(row, builder);
        row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(box), 0);
    }
}

gboolean mx_stop_search_room(gpointer *entry,
                             gpointer *data, GtkBuilder *builder) {
    GObject *listbox = gtk_builder_get_object(builder, "listbox_rooms");
    GObject *sentry = gtk_builder_get_object(builder, "sentry_rooms");

    if (!mx_get_selected_groom(builder, MX_GLOBAL_ROOMS)) {
        mx_search_delim_set_visibility(builder, FALSE);
        gtk_entry_set_text(GTK_ENTRY(sentry), "");
        gtk_list_box_set_filter_func(GTK_LIST_BOX(listbox), NULL, NULL, NULL);
        gtk_list_box_invalidate_filter(GTK_LIST_BOX(listbox));
        mx_widget_set_visibility_by_name(builder,
                                        "label_search_nothing_local", FALSE);
        mx_clear_global_search(builder);
    }
    (void)entry;
    (void)data;
    return FALSE;
}
