#include "client.h"

void mx_swap_room(GtkListBox *box, GtkListBoxRow *row, GtkBuilder *builder) {
    puts("Fuck this shit!");
    box++;
    row++;
    builder++;
    // gtk_stack_set_visible_child_name(stack, "msg_2");
}

void mx_swap(GtkListBoxRow *row, GtkBuilder *builder) {
    puts("WOOOOORK!");
    row++;
    builder++;
}

static void add_room_row(GtkBuilder *builder) {
    GtkListBox *box = GTK_LIST_BOX(gtk_builder_get_object(builder, "listbox_rooms"));
    GtkWidget *row = gtk_list_box_row_new();
    GtkWidget *label = gtk_label_new(mx_get_buffer_text("buffer_roomname", builder));

    gtk_container_add(GTK_CONTAINER(row), label);
    gtk_widget_set_size_request(row, -1, 80);

    gtk_list_box_insert(box, row, -1);
    gtk_widget_show_all(GTK_WIDGET(box));
    mx_scrlldwnd_connect("scrlldwnd_rooms", builder);
}

static void add_messege_room(GtkBuilder *builder) {
    GtkWidget *stack = GTK_WIDGET(gtk_builder_get_object(builder, "stack_messege_rooms"));
    GtkWidget *label = gtk_label_new("MESSAGES SHOULD BE HERE");

    gtk_stack_add_named(GTK_STACK(stack), label, "msg_room_1");
    gtk_widget_show_all(GTK_WIDGET(stack));
}

void mx_create_room(GtkButton *btn, GtkBuilder *builder) {
    btn++;
    add_room_row(builder);
    add_messege_room(builder);
}
