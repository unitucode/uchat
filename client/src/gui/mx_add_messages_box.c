#include "client.h"

static void create_viewport(GtkWidget *scroll, GtkWidget *box) {
    GtkWidget *view = gtk_viewport_new(NULL, NULL);

    gtk_container_add(GTK_CONTAINER(scroll), view);
    gtk_container_add(GTK_CONTAINER(view), box);
}

void mx_add_messages_box(t_groom *room, t_chat *chat) {
    GObject *stack = gtk_builder_get_object(chat->builder,
                                            "stack_messege_rooms");
    GtkWidget *box = gtk_list_box_new();
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);

    create_viewport(scroll, box);
    gtk_widget_set_can_focus(box, FALSE);
    room->box_messages = GTK_LIST_BOX(box);
    gtk_list_box_set_selection_mode(room->box_messages,
                                    GTK_SELECTION_MULTIPLE);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),
                                   GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_stack_add_named(GTK_STACK(stack), scroll, mx_msgpage_name(room->id));
    room->stack_msg = GTK_STACK(stack);
    room->page = GTK_SCROLLED_WINDOW(scroll);
    gtk_widget_show_all(scroll);
    mx_scrlldwnd_connect(NULL, scroll, chat->builder, room);
    g_signal_connect(scroll, "edge-reached",
                     G_CALLBACK(mx_box_messages_reached), chat);
}
