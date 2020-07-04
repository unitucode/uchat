#include "client.h"

gchar *mx_get_text_from_buffer(GtkTextBuffer *buffer) {
    GtkTextIter start;
    GtkTextIter end;

    gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(buffer), &start);
    gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(buffer), &end);
    return gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer),
                                    &start, &end, FALSE);
}

static GtkWidget *window_create() {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);;
    
    gtk_window_set_title(GTK_WINDOW(window), "Unit test - Requests");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 70);
    gtk_window_set_position(GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    return window;
}

int mx_gui_unit_test(t_chat *chat, int argc, char **argv) {
    GtkWidget *window;

    gtk_init(&argc, &argv);
    window = window_create();
    mx_activate_content_test(window, chat);
    g_signal_connect(window, "delete-event", G_CALLBACK (gtk_main_quit), NULL);
    gtk_main();
    return 0;
}

void mx_activate_content_test(GtkWidget *window, t_chat *chat) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *textview = gtk_text_view_new();
    GtkWidget *btn = gtk_button_new_with_label("Send");

    g_object_set_data(G_OBJECT(btn), "textview", textview);
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
    g_signal_connect(btn, "clicked", G_CALLBACK(mx_get_buffer_text_unit),
                     chat);
    gtk_widget_show_all(window);
}

void mx_get_buffer_text_unit(GtkButton *btn, t_chat *chat) {
    GObject *textview = g_object_get_data(G_OBJECT(btn), "textview");
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
    gchar *buf = mx_get_text_from_buffer(buffer);
    cJSON_Minify(buf);
    t_dtp *req = mx_request_creation(buf);

    mx_send(chat->out, req);
    mx_free_request(&req);
}
