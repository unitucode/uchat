#include "client.h"

gchar *mx_get_buffer_text(GtkTextBuffer *buffer) {
    GtkTextIter start;
    GtkTextIter end;

    if (GTK_IS_TEXT_BUFFER(buffer)) {
        gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(buffer), &start);
        gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(buffer), &end);
        return gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer),
                                        &start, &end, FALSE);
    }
    else
        return (gchar*)gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER(buffer));
}

static void get_text_from_textview(GtkButton *btn, GtkTextView *textview) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);

    puts(mx_get_buffer_text(buffer));
}

static GtkWidget *window_create(GtkApplication* app) {
    GtkWidget *window = gtk_application_window_new(app);
    
    gtk_window_set_title (GTK_WINDOW(window), "Unit test - Requests");
    gtk_window_set_default_size (GTK_WINDOW(window), 400, 70);
    gtk_window_set_position(GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    return window;
}

static void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget *window = window_create(app);
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *textview = gtk_text_view_new();
    GtkWidget *btn = gtk_button_new_with_label("Send");

    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(textview), 8);
    gtk_text_view_set_top_margin(GTK_TEXT_VIEW(textview), 8);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_WORD_CHAR);
    gtk_widget_set_margin_top(box, 15);
    gtk_widget_set_margin_bottom(box, 15);
    gtk_widget_set_margin_end(box, 8);
    gtk_widget_set_margin_start(box, 8);
    gtk_box_pack_start(GTK_BOX(box), textview, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(box), btn, FALSE, TRUE, 5);
    g_signal_connect(btn, "clicked", G_CALLBACK(get_text_from_textview),
                     GTK_TEXT_VIEW(textview));
    gtk_widget_show_all(window);
}

static int pasha(t_chat *chat, int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}

int main (int argc, char **argv) {
    GSocketConnection *connection = NULL;
    GSocketClient *client = g_socket_client_new();
    t_chat *chat = NULL;

    change_working_dir();
    if (!is_valid(argc))
        return -1;
    connection = g_socket_client_connect_to_host(
        client, argv[1], g_ascii_strtoll(argv[2], NULL, 10), NULL, NULL);
    if (!connection) {
        g_printerr("Invalid port or ip\n");
        return -1;
    }
    pasha(chat, argc, argv);
    // chat = mx_init_chat(connection, argc, argv);
    // chat->cli_conn = client;
    // mx_init_gui(chat);
    // mx_start_gui(chat);
    return 0;
}
