#include "client.h"

static int flag = 1;

gboolean mx_set_placeholder(GtkWidget *textview, GdkEvent *event,
                                   gpointer *user_data) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
    const gchar *placeholder = "Enter your message";
    GtkTextIter start;
    GtkTextIter end;

    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    if (strlen(gtk_text_buffer_get_text(buffer, &start, &end, FALSE)) == 0) {
        gtk_text_buffer_set_text(buffer, placeholder, -1);
        flag = 1;
    }
    (void)event;
    (void)user_data;
    return FALSE;
}

gboolean mx_unset_placeholder(GtkWidget *textview, GdkEvent  *event,
                                   gpointer *user_data) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
    const gchar *placeholder = "";
    
    if (flag) {
        gtk_text_buffer_set_text(buffer, placeholder, -1);
        flag = 0;
    }
    //puts("Hello I'm -IN-");
    (void)event;
    (void)user_data;
    return FALSE;
}
