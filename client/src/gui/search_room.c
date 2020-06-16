#include "client.h"

static gboolean filter_room_name(GtkListBoxRow *row, char *search_name) {
    t_groom *groom = (t_groom*)g_object_get_data(G_OBJECT(row), "groom");
    char *room_name = (char*)gtk_label_get_text(groom->label_name);

    if (!strncmp(room_name, search_name, strlen(search_name)))
        return TRUE;
    else
        return FALSE;
}

gboolean mx_disable_listbox_filter(gpointer *entry, gpointer *data2,
                               GObject *listbox) {
    if (GTK_IS_ENTRY(entry))
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    gtk_list_box_set_filter_func(GTK_LIST_BOX(listbox), NULL, NULL, NULL);
    gtk_list_box_invalidate_filter(GTK_LIST_BOX(listbox));
    (void)data2;
    return FALSE;
}

void mx_search_room(GtkSearchEntry *sentry, GtkBuilder *builder) {
    char *search_name = mx_entry_get_text("sentry_rooms", builder);
    GObject *listbox = gtk_builder_get_object(builder, "listbox_rooms");

    gtk_list_box_set_filter_func(GTK_LIST_BOX(listbox),
                                (GtkListBoxFilterFunc)filter_room_name,
                                search_name, NULL);
    if (!strlen(search_name))
        mx_disable_listbox_filter(NULL, NULL, listbox);
    (void)sentry;
}
