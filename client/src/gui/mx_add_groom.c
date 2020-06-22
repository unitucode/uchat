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

void mx_set_current_room_sett(GtkBuilder *builder) {
    t_groom *groom = mx_get_selected_groom(builder);
    GObject *name = gtk_builder_get_object(builder, "label_prefs_roomname");
    GObject *customer = gtk_builder_get_object(builder,
                                               "label_prefs_customer");
    GObject *desc = gtk_builder_get_object(builder, "buffer_room_desc");
    GObject *header_name = gtk_builder_get_object(builder,
                                                  "label_header_roomname");

    gtk_label_set_text(GTK_LABEL(name), groom->room_name);
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(desc), groom->desc, -1);
    gtk_label_set_text(GTK_LABEL(customer), groom->customer);
    gtk_label_set_text(GTK_LABEL(header_name), groom->room_name);
}

void mx_select_room(GtkWidget *event_box, GdkEventButton *event,
                    gpointer *user_data) {
    t_signal_data *data = g_object_get_data(G_OBJECT(event_box), "sigdata");

    mx_reset_messege_room(data->groom, data->builder);
    gtk_stack_set_visible_child(data->groom->stack_msg,
                                GTK_WIDGET(data->groom->page));
    gtk_list_box_select_row(data->groom->box_rooms,
                            data->groom->row_room);
    mx_set_current_room_sett(data->builder);
    mx_set_room_widgets_visibility(data->builder, true);
    (void)event;
    (void)user_data;
}

void mx_join_to_room(GtkWidget *event_box, GdkEventButton *event,
                     gpointer *user_data) {
    t_signal_data *data = g_object_get_data(G_OBJECT(event_box), "sigdata");

    mx_reset_messege_room(data->groom, data->builder);
    gtk_list_box_select_row(data->groom->box_rooms,
                            data->groom->row_room);
    puts("JOINING TO ROOM");
    (void)event;
    (void)user_data;
}

//================================

gint mx_room_sort(GtkListBoxRow *row1, GtkListBoxRow *row2) {
    t_groom *f_room = g_object_get_data(G_OBJECT(row1), "groom");

    if (f_room->is_updated) {
        return false;
    }
    (void)row2;
    return true;
}

static void add_messages_box(t_groom *room, GtkBuilder *builder) {
    GObject *stack = gtk_builder_get_object(builder, "stack_messege_rooms");
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
    mx_scrlldwnd_connect(NULL, scroll, builder);
}

void mx_add_room_row(t_groom *room, GtkBuilder *builder, gchar *listbox_name) {
    GtkListBox *box = GTK_LIST_BOX(gtk_builder_get_object(builder,
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

    data = mx_create_sigdata(builder, room, NULL);
    if (!g_strcmp0(listbox_name, MX_LISTBOX_LOCAL_ROOMS)) {
        g_signal_connect(event, "button_press_event",
                        G_CALLBACK(mx_select_room), NULL);
    }
    else {
        g_signal_connect(event, "button_press_event",
                         G_CALLBACK(mx_join_to_room), NULL);
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

void mx_add_groom(t_groom *room, GtkBuilder *builder) {
    add_messages_box(room, builder);
    mx_add_room_row(room, builder, MX_LISTBOX_LOCAL_ROOMS);
}

static t_groom *mx_init_groom() {
    t_groom *room = mx_malloc(sizeof(t_groom));

    room->room_name = NULL;
    room->customer = NULL;
    room->box_rooms = NULL;
    room->box_messages = NULL;
    room->page = NULL;
    room->row_room = NULL;
    room->stack_msg = NULL;
    room->id = -1;
    room->date = -1;
    room->is_updated = true;
    room->desc = NULL;
    room->members = g_hash_table_new(g_direct_hash, g_direct_equal);
    return room;
}

void mx_free_sigdata(t_signal_data *data) {
    mx_free((void **)&data);
}

static bool get_data(cJSON *msg, cJSON **data, char *field) { // TO FIX IN GMSG GET_DATA
    *data = cJSON_GetObjectItemCaseSensitive(msg, field);
    if (!*data)
        return false;
    return true;
}

t_groom *mx_create_groom(cJSON *room) {
    t_groom *groom = mx_init_groom();
    cJSON *data = NULL;
    bool valid = true;

    if ((valid = get_data(room, &data, "name")) && cJSON_IsString(data))
        groom->room_name = strdup(data->valuestring);
    if ((valid = get_data(room, &data, "customer_id")) && cJSON_IsNumber(data))
        groom->customer = strdup("TODO ID");
    if ((valid = get_data(room, &data, "id")) && cJSON_IsNumber(data))
        groom->id = data->valueint;
    if ((valid = get_data(room, &data, "date")) && cJSON_IsNumber(data))
        groom->date = data->valueint;
    if ((valid = get_data(room, &data, "desc")) && cJSON_IsString(data))
        groom->desc = strdup(data->valuestring);
    if (!valid) {
        mx_delete_groom(groom);
        return NULL;
    }
    return groom;
}

void mx_delete_groom(t_groom *room) {
    if (room) {
        mx_free((void**)&(room->room_name));
        mx_free((void**)&(room->customer));
        mx_free((void**)&(room->desc));
        mx_free((void**)&room);
        room = NULL;
    }
}
