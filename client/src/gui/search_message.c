#include "client.h"

void mx_add_message_to_found(t_gmsg *gmsg, t_chat *chat) {
    GtkWidget *row = gtk_list_box_row_new();
    GtkWidget *event = mx_create_message_row(chat, gmsg);
    GObject *box = gtk_builder_get_object(chat->builder,
                                          "listbox_found_msgs");

    gtk_widget_set_can_focus(row, FALSE);
    gmsg->row_msg = GTK_LIST_BOX_ROW(row);
    g_object_ref(row);
    gtk_container_add(GTK_CONTAINER(row), event);
    gtk_list_box_insert(GTK_LIST_BOX(box), row, -1);
    gtk_widget_show_all(GTK_WIDGET(box));
}

void mx_clear_found_msgs(GtkBuilder *builder) {
    GObject *box = (gtk_builder_get_object(builder, "listbox_found_msgs"));
    GtkListBoxRow *row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(box), 0);

    mx_widget_set_visibility_by_name(builder,
                                     "label_search_nothing_msgs", FALSE);
    while (row) {
        gtk_widget_destroy(GTK_WIDGET(row));
        row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(box), 0);
    }
    mx_widget_set_visibility_by_name(builder, "stack_messege_rooms", TRUE);
    mx_widget_set_visibility_by_name(builder, "scrlldwnd_found_msgs", FALSE);
    mx_widget_set_visibility_by_name(builder, "label_found_messages", FALSE);
}

gboolean mx_stop_search_message(gpointer *entry,
                                gpointer *data, GtkBuilder *builder) {
    GObject *sentry = gtk_builder_get_object(builder, "sentry_messages");

    gtk_entry_set_text(GTK_ENTRY(sentry), "");
    mx_clear_found_msgs(builder);
    (void)entry;
    (void)data;
    return FALSE;
}
