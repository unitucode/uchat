#include "client.h"

void mx_swap_room(GtkWidget *widget, GdkEventButton *event, t_groom *room) {
    gtk_stack_set_visible_child(room->stack_msg, GTK_WIDGET(room->box_msg));
    gtk_list_box_select_row(room->box_rooms, room->row_room);
    (void)widget;
    (void)event;
}

static void add_messages_box(t_groom *room, GtkBuilder *builder) {
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(builder,
                                                       "stack_messege_rooms"));
    GtkWidget *box = gtk_list_box_new();

    gtk_stack_add_named(stack, box, NULL);
    room->stack_msg = stack;
    room->box_msg = GTK_LIST_BOX(box);
    gtk_widget_show_all(box);
}

static void add_room_row(t_groom *room, GtkBuilder *builder) {
    GtkListBox *box = GTK_LIST_BOX(gtk_builder_get_object(builder, "listbox_rooms"));
    GtkWidget *row = gtk_list_box_row_new();
    GtkWidget *label = gtk_label_new(mx_get_buffer_text("buffer_roomname", builder));
    GtkWidget *event = gtk_event_box_new();

    room->box_rooms = box;
    room->row_room = GTK_LIST_BOX_ROW(row);
    g_signal_connect(event, "button_press_event",
                     G_CALLBACK(mx_swap_room), room);

    gtk_container_add(GTK_CONTAINER(event), label);
    gtk_container_add(GTK_CONTAINER(row), event);
    gtk_widget_set_size_request(row, -1, 80);

    gtk_list_box_insert(box, row, -1);
    gtk_widget_show_all(GTK_WIDGET(box));
    mx_scrlldwnd_connect("scrlldwnd_rooms", builder);
}

void mx_create_room(GtkButton *btn, GtkBuilder *builder) {
    t_groom *room = malloc(sizeof(t_groom));

    add_messages_box(room, builder);
    add_room_row(room, builder);
    (void)btn;
}
