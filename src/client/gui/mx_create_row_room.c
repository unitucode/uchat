#include "client.h"

// void check(GtkWidget *widget, GdkEventButton *event, t_lbroom *data) {
//     gtk_list_box_select_row(data->box, data->row);
//     puts("WOOOOORK!");
//     widget++;
//     event++;
// }
// 
// static void add_room_row(GtkBuilder *builder) {
//     GtkListBox *box = GTK_LIST_BOX(gtk_builder_get_object(builder, "listbox_rooms"));
//     GtkWidget *row = gtk_list_box_row_new();
//     GtkWidget *label = gtk_label_new(mx_get_buffer_text("buffer_roomname", builder));
//     GtkWidget *event = gtk_event_box_new();
// 
//     t_lbroom *data = malloc(sizeof(t_lbroom));
//     data->box = GTK_LIST_BOX(box);
//     data->row = GTK_LIST_BOX_ROW(row);
//     g_signal_connect(event, "button_press_event", G_CALLBACK(check), data);
// 
//     gtk_container_add(GTK_CONTAINER(event), label);
//     gtk_container_add(GTK_CONTAINER(row), event);
//     gtk_widget_set_size_request(row, -1, 80);
// 
//     gtk_list_box_insert(box, row, -1);
//     gtk_widget_show_all(GTK_WIDGET(box));
//     mx_scrlldwnd_connect("scrlldwnd_rooms", builder);
// }
// 
// void mx_create_room(GtkButton *btn, GtkBuilder *builder) {
//     // add_room_row(builder);
//     // add_messege_room(builder);
// }
