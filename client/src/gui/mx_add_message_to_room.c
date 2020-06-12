#include "client.h"

// SIGNAL-HANDLERS
void mx_select_msg(GtkWidget *widget, GdkEventButton *event,
                   t_signal_data *data) {
    GObject *control = gtk_builder_get_object(data->builder,
                                              "btnbox_msg_ctrl");
    t_groom *groom = mx_get_selected_groom(data->builder);

    if (gtk_list_box_row_is_selected(GTK_LIST_BOX_ROW(data->row_msg))) {
        gtk_widget_set_visible(GTK_WIDGET(control), false);
        gtk_list_box_unselect_row(GTK_LIST_BOX(groom->box_messages),
                                  GTK_LIST_BOX_ROW(data->row_msg));
    }
    else {
        gtk_widget_set_visible(GTK_WIDGET(control), true);
        gtk_list_box_select_row(GTK_LIST_BOX(groom->box_messages),
                                GTK_LIST_BOX_ROW(data->row_msg));
    }
    (void)widget;
    (void)event;
}
//==============================

static void add_message_row(t_gmsg *msg, GtkBuilder *builder) {
    GtkWidget *row = gtk_list_box_row_new();
    GtkWidget *event = mx_create_message_row(msg);
    t_groom *room = mx_get_groom_by_name(msg->room_name, builder);
    GtkListBox *box = room->box_messages;
    t_signal_data *data = (t_signal_data*)malloc(sizeof(t_signal_data));

    data->builder = builder;
    data->msg = msg;
    data->row_msg = row;

    gtk_container_add(GTK_CONTAINER(row), event);
    g_signal_connect(event, "button_press_event",
                     G_CALLBACK(mx_select_msg), data);
    room->is_updated = true;
    gtk_list_box_insert(box, row, -1);
    gtk_list_box_row_changed(room->row_room);
    room->is_updated = false;
    gtk_widget_show_all(GTK_WIDGET(box));
}

void mx_add_message_to_room(t_gmsg *msg, GtkBuilder *builder) {
    add_message_row(msg, builder);
}
