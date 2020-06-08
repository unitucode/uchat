#include "client.h"

// SIGNAL-HANDLERS
void mx_reset_addroom(GtkButton *btn, GtkBuilder *builder) {
    GObject *button = gtk_builder_get_object(builder, "checkbtn_private");

    mx_clear_buffer_text("buffer_roomname", builder);
    mx_clear_buffer_text("buffer_roompass", builder);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), 0);
    (void)btn;
}

void mx_make_private(GtkToggleButton *btn, GtkWidget *widget) {
    gtk_widget_set_sensitive(widget, gtk_toggle_button_get_active(btn));
}

void mx_swap_room(GtkWidget *widget, GdkEventButton *event, t_groom *room) {
    gtk_stack_set_visible_child(room->stack_msg, GTK_WIDGET(room->page));
    gtk_list_box_select_row(room->box_rooms, room->row_room);
    (void)widget;
    (void)event;
}
//================================

static void add_messages_box(t_groom *room, GtkBuilder *builder) {
    GObject *stack = gtk_builder_get_object(builder, "stack_messege_rooms");
    GtkWidget *box = gtk_list_box_new();
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *view = gtk_viewport_new(NULL, NULL);

    room->box_messages = box;
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),
                                   GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scroll), view);
    gtk_container_add(GTK_CONTAINER(view), box);

    gtk_stack_add_named(GTK_STACK(stack), scroll, room->room_name);
    room->stack_msg = GTK_STACK(stack);
    room->page = GTK_SCROLLED_WINDOW(scroll);
    gtk_widget_show_all(scroll);
    mx_scrlldwnd_connect(NULL, scroll, builder);
}

static void add_room_row(t_groom *room, GtkBuilder *builder) {
    GtkListBox *box = GTK_LIST_BOX(gtk_builder_get_object(builder,
                                                          "listbox_rooms"));
    GtkWidget *row = gtk_list_box_row_new();
    GtkWidget *label = gtk_label_new(room->room_name);
    GtkWidget *event = gtk_event_box_new();

    g_object_set_data_full(G_OBJECT(row), "groom", room,
                           (GDestroyNotify)mx_delete_groom);
    room->box_rooms = box;
    room->row_room = GTK_LIST_BOX_ROW(row);
    g_signal_connect(event, "button_press_event",
                     G_CALLBACK(mx_swap_room), room);
    gtk_container_add(GTK_CONTAINER(event), label);
    gtk_container_add(GTK_CONTAINER(row), event);
    gtk_widget_set_size_request(row, -1, 80);

    gtk_list_box_insert(box, row, -1);
    gtk_widget_show_all(GTK_WIDGET(box));
}

void mx_add_groom(t_groom *room, GtkBuilder *builder) {
    add_messages_box(room, builder);
    add_room_row(room, builder);
}

t_groom *mx_create_groom(char *room_name, char *customer, int id,
                         long int date) {
    t_groom *room = mx_malloc(sizeof(t_groom));

    room->room_name = strdup(room_name);
    room->customer = strdup(customer);
    room->box_rooms = NULL;
    room->box_messages = NULL;
    room->page = NULL;
    room->row_room = NULL;
    room->stack_msg = NULL;
    room->id = id;
    room->date = date;
    return room;
}

void mx_delete_groom(t_groom *room) {
    if (room) {
        mx_free((void**)&room->room_name);
        mx_free((void**)&room->customer);
    }
}
