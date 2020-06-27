#include "client.h"

gint mx_room_sort(GtkListBoxRow *row1, GtkListBoxRow *row2) {
    t_groom *f_room = g_object_get_data(G_OBJECT(row1), "groom");

    if (f_room->is_updated) {
        return false;
    }
    (void)row2;
    return true;
}

static void add_messages_box(t_groom *room, t_chat *chat) {
    GObject *stack = gtk_builder_get_object(chat->builder,
                                            "stack_messege_rooms");
    GtkWidget *box = gtk_list_box_new();
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *view = gtk_viewport_new(NULL, NULL);

    room->box_messages = GTK_LIST_BOX(box);
    gtk_list_box_set_selection_mode(room->box_messages, GTK_SELECTION_MULTIPLE);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),
                                   GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scroll), view);
    gtk_container_add(GTK_CONTAINER(view), box);

    gtk_stack_add_named(GTK_STACK(stack), scroll, mx_msgpage_name(room->id));
    room->stack_msg = GTK_STACK(stack);
    room->page = GTK_SCROLLED_WINDOW(scroll);
    gtk_widget_show_all(scroll);
    mx_scrlldwnd_connect(NULL, scroll, chat->builder);
    g_signal_connect(scroll, "edge-reached",
                     G_CALLBACK(mx_box_messages_reached), chat);
}

void mx_add_room_row(t_groom *room, t_chat *chat, gchar *listbox_name) {
    GtkListBox *box = GTK_LIST_BOX(gtk_builder_get_object(chat->builder,
                                                          listbox_name));
    GtkWidget *row = gtk_list_box_row_new();
    GtkWidget *label = gtk_label_new(room->room_name);
    GtkWidget *event = gtk_event_box_new();
    t_signal_data *data = NULL;

    room->box_rooms = box;
    room->row_room = GTK_LIST_BOX_ROW(row);
    room->label_name = GTK_LABEL(label);
    g_object_ref(box);
    g_object_ref(row);
    g_object_ref(label);

    data = mx_create_sigdata(chat, room, NULL);
    if (!g_strcmp0(listbox_name, MX_LOCAL_ROOMS)) {
        g_signal_connect(event, "button_press_event",
                        G_CALLBACK(mx_select_room), NULL);
    }
    else {
        g_signal_connect(event, "button_press_event",
                         G_CALLBACK(mx_show_join_to_room), NULL);
    }

    gtk_label_set_ellipsize(GTK_LABEL(label), PANGO_ELLIPSIZE_END);
    gtk_container_add(GTK_CONTAINER(event), label);
    gtk_container_add(GTK_CONTAINER(row), event);
    gtk_widget_set_size_request(row, -1, 80);
    gtk_list_box_set_sort_func(box, (GtkListBoxSortFunc)mx_room_sort, NULL, NULL);
    room->is_updated = false;

    gtk_list_box_insert(box, row, -1);
    gtk_widget_show_all(GTK_WIDGET(box));

    g_object_set_data_full(G_OBJECT(row), "groom", room,
                           (GDestroyNotify)mx_delete_groom);
    g_object_set_data_full(G_OBJECT(event), "sigdata", data,
                            (GDestroyNotify)mx_free_sigdata);
}

void mx_add_groom(t_groom *room, t_chat *chat) {
    add_messages_box(room, chat);
    mx_add_room_row(room, chat, MX_LOCAL_ROOMS);
}
