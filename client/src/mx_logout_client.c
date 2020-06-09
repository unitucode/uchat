#include "client.h"

void mx_set_default_room_sett(GtkBuilder *builder) {
    GObject *name = gtk_builder_get_object(builder, "label_prefs_roomname");
    GObject *customer = gtk_builder_get_object(builder,
                                               "label_prefs_customer");
    GObject *header = gtk_builder_get_object(builder, "header_main");

    gtk_label_set_text(GTK_LABEL(name), "Room Name");
    gtk_header_bar_set_title(GTK_HEADER_BAR(header), "UChat");
    gtk_label_set_text(GTK_LABEL(customer), "customer login");
}

void mx_unselect_room(t_groom *groom, GtkBuilder *builder) {
    mx_set_default_room_sett(builder);
    gtk_widget_hide(GTK_WIDGET(groom->row_room));
    gtk_widget_hide(GTK_WIDGET(groom->page));
}

void mx_delete_row_room(GtkWidget *row, GtkBuilder *builder) {
    t_groom *groom = g_object_get_data(G_OBJECT(row), "groom");

    if (gtk_list_box_row_is_selected(GTK_LIST_BOX_ROW(row)))
        mx_unselect_room(groom, builder);
    gtk_widget_destroy(GTK_WIDGET(groom->page));
    gtk_widget_destroy(row);
}

void mx_logout_client(t_chat *chat) {
    GtkListBox *box = GTK_LIST_BOX(gtk_builder_get_object(chat->builder,
                                                          "listbox_rooms"));
    GtkListBoxRow *row = gtk_list_box_get_row_at_index(box, 0);

    mx_delete_row_room(GTK_WIDGET(row), chat->builder);
}
