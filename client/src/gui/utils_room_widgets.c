#include "client.h"

void mx_switch_room_header(GtkBuilder *builder, gint page_index) {
    GObject *stack = gtk_builder_get_object(builder, "stack_room_header");
    GObject *page = NULL;

    if (page_index == MX_ROOM_CTRL)
        page = gtk_builder_get_object(builder, "box_room_ctrl");
    else if (page_index == MX_MSG_CTRL)
        page = gtk_builder_get_object(builder, "box_msg_ctrl");
    gtk_stack_set_visible_child(GTK_STACK(stack), GTK_WIDGET(page));
}

void mx_set_room_widgets_visibility(GtkBuilder *builder,
                                    gboolean visibility) {
    GObject *box_entry = gtk_builder_get_object(builder, "box_entry_field");
    GObject *box_header = gtk_builder_get_object(builder, "box_room_header");
    GObject *box_editing = gtk_builder_get_object(builder, "box_editing_msg");
    GObject *box_stickers = gtk_builder_get_object(builder, "box_stickers");

    if (visibility) {
        mx_switch_room_header(builder, MX_ROOM_CTRL);
        gtk_widget_show_all(GTK_WIDGET(box_entry));
        gtk_widget_show_all(GTK_WIDGET(box_header));
    }
    else {
        gtk_widget_hide(GTK_WIDGET(box_entry));
        gtk_widget_hide(GTK_WIDGET(box_header));
        gtk_widget_hide(GTK_WIDGET(box_editing));
        gtk_widget_hide(GTK_WIDGET(box_stickers));
    }
}

void mx_set_default_room_sett(GtkBuilder *builder) {
    GObject *name = gtk_builder_get_object(builder, "label_prefs_roomname");
    GObject *customer = gtk_builder_get_object(builder,
                                               "label_prefs_customer");
    GObject *desc = gtk_builder_get_object(builder, "buffer_room_desc");

    gtk_label_set_text(GTK_LABEL(name), "Room Name");
    gtk_label_set_text(GTK_LABEL(customer), "customer login");
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(desc), "", -1);
}
