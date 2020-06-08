#include "client.h"

static GtkWidget *get_current_msgbox(GtkBuilder *builder) {
    GtkStack *stack = GTK_STACK(gtk_builder_get_object(builder,
                                                       "stack_messege_rooms"));
    GtkWidget *page = gtk_stack_get_visible_child(stack);
    GList *list_page = gtk_container_get_children(GTK_CONTAINER(page));
    GList *list_view = gtk_container_get_children(GTK_CONTAINER(list_page->data));
    return GTK_WIDGET(list_view->data);
}

static void add_message_row(t_gmsg *msg, GtkBuilder *builder) {
    GtkWidget *row = mx_create_message_row(msg);
    GtkWidget *box = get_current_msgbox(builder);

    gtk_list_box_insert(GTK_LIST_BOX(box), row, -1);
    gtk_widget_show_all(GTK_WIDGET(box));
}

void mx_add_message_to_room(t_gmsg *msg, GtkBuilder *builder) {
    mx_clear_buffer_text("buffer_message", builder);
    add_message_row(msg, builder);
}
