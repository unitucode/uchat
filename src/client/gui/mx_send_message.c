#include "client.h"

static GtkWidget *get_current_msgbox(GtkBuilder *builder) {
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(builder,
                                                       "stack_messege_rooms"));
    GtkWidget *page = gtk_stack_get_visible_child(stack);
    GList *list_page = gtk_container_get_children(GTK_CONTAINER(page));
    GList *list_view = gtk_container_get_children(GTK_CONTAINER(list_page->data));
    return GTK_WIDGET(list_view->data);
}

static void add_message_row(gchar *msg, GtkBuilder *builder) {
    GtkWidget *row = gtk_list_box_row_new();
    GtkWidget *label = gtk_label_new(msg);
    GtkWidget *box = get_current_msgbox(builder);

    gtk_container_add(GTK_CONTAINER(row), label);
    gtk_widget_set_size_request(row, -1, 60);

    gtk_list_box_insert(GTK_LIST_BOX(box), row, -1);
    gtk_widget_show_all(GTK_WIDGET(box));
    // mx_scrlldwnd_connect("scrlldwnd_room", builder);
}

void mx_send_message(GtkButton *btn, GtkBuilder *builder) {
    gchar *message_text = mx_get_buffer_text("buffer_message", builder);
    
    mx_clear_buffer_text("buffer_message", builder);
    add_message_row(message_text, builder);
    (void)btn;
}
