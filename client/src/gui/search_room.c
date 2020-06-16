#include "client.h"

static gboolean filter_room_name(GtkListBoxRow *row, char *search_name) {
    t_groom *groom = (t_groom*)g_object_get_data(G_OBJECT(row), "groom");
    char *room_name = (char*)gtk_label_get_text(groom->label_name);

    if (!strncmp(room_name, search_name, strlen(search_name)))
        return TRUE;
    else
        return FALSE;
}

void mx_search_room(GtkSearchEntry *sentry, GtkBuilder *builder) {
    char *search_name = mx_entry_get_text("sentry_rooms", builder);
    GObject *listbox = gtk_builder_get_object(builder, "listbox_rooms");

    gtk_list_box_set_filter_func(GTK_LIST_BOX(listbox),
                                 (GtkListBoxFilterFunc)filter_room_name,
                                 search_name, NULL);
    (void)sentry;
}

void mx_sentry_stop(GObject *sentry, GtkEntryIconPosition icon_pos, GdkEvent *event, GtkBuilder *builder) {
    // GObject *listbox = gtk_builder_get_object(builder, "listbox_rooms");
    
    // gtk_list_box_set_filter_func(GTK_LIST_BOX(listbox), NULL, NULL, NULL);
    if (icon_pos == GTK_ENTRY_ICON_SECONDARY) {
        gtk_widget_hide(GTK_WIDGET(sentry));
        gtk_widget_show(GTK_WIDGET(sentry));
    }
    (void)event;
    (void)builder;
}
