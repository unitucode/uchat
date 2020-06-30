#include "client.h"

static gboolean filter_member_login(GtkListBoxRow *row, gchar *search_login) {
    GList *gl_row = gtk_container_get_children(GTK_CONTAINER(row));
    GList *gl_box = gtk_container_get_children(GTK_CONTAINER(gl_row->data));
    GtkLabel *label = GTK_LABEL(gl_box->data);
    gchar *login = (gchar*)gtk_label_get_text(label);

    if (!g_ascii_strncasecmp(login, search_login, strlen(search_login)))
        return TRUE;
    else
        return FALSE;
}

void mx_search_members(GtkBuilder *builder, gchar *search_login) {
    GObject *listbox = gtk_builder_get_object(builder,
                                              "listbox_info_members");

    gtk_list_box_set_filter_func(GTK_LIST_BOX(listbox),
                                 (GtkListBoxFilterFunc)filter_member_login,
                                 search_login, NULL);
}

gboolean mx_stop_search_members(gpointer *entry,
                                gpointer *data, GtkBuilder *builder) {
    GObject *listbox = gtk_builder_get_object(builder,
                                              "listbox_info_members");
    GObject *sentry = gtk_builder_get_object(builder, "sentry_messages");

    gtk_entry_set_text(GTK_ENTRY(sentry), "");
    gtk_list_box_set_filter_func(GTK_LIST_BOX(listbox), NULL, NULL, NULL);
    gtk_list_box_invalidate_filter(GTK_LIST_BOX(listbox));
    (void)data;
    (void)entry;
    return FALSE;
}
