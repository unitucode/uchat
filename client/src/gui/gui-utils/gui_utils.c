#include "client.h"

gchar *mx_get_buffer_text(char *buff_name, GtkBuilder *builder) {
    GObject *buffer = gtk_builder_get_object(builder, buff_name);
    GtkTextIter start;
    GtkTextIter end;

    if (GTK_IS_TEXT_BUFFER(buffer)) {
        gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(buffer), &start);
        gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(buffer), &end);
        return gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer), &start, &end, FALSE);
    }
    else
        return (gchar*)gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER(buffer));
}

void mx_clear_buffer_text(char *buff_name, GtkBuilder *builder) {
    GObject *buffer = gtk_builder_get_object(builder, buff_name);
    GtkTextIter start;
    GtkTextIter end;

    if (GTK_IS_TEXT_BUFFER(buffer)) {
        gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(buffer), &start);
        gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(buffer), &end);
        gtk_text_buffer_delete(GTK_TEXT_BUFFER(buffer), &start, &end);
    }
    else
        gtk_entry_buffer_delete_text(GTK_ENTRY_BUFFER(buffer), 0, -1);
}

void mx_widget_set_visibility(GtkWidget *widget, gboolean is_visible) {
    if (is_visible)
        gtk_widget_show(widget);
    else
        gtk_widget_hide(widget);    
}

void mx_widget_set_visibility_by_name(GtkBuilder *builder,
                                      gchar *name, gboolean is_visible) {
    GtkWidget *widget = GTK_WIDGET(gtk_builder_get_object(builder, name));

    mx_widget_set_visibility(widget, is_visible);
}

void mx_widget_switch_visibility_by_name(GtkBuilder *builder, gchar *name) {
    GtkWidget *widget = GTK_WIDGET(gtk_builder_get_object(builder, name));

    mx_widget_switch_visibility(NULL, widget);
}

void mx_widget_switch_visibility(GtkWidget *usr_ctrl, GtkWidget *widget) {
    mx_widget_set_visibility(widget, !gtk_widget_is_visible(widget));
    (void)usr_ctrl;
}

void mx_focus_out(GtkWidget *widget, GdkEvent *event, gpointer *user_data) {
    gtk_widget_hide(widget);
    (void)user_data;
    (void)event;
}

void mx_clear_label_by_name(char *label_name, GtkBuilder *builder) {
    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder, label_name));

    gtk_label_set_text(label, "\0");
}

gchar *mx_entry_get_text(char *entry_name, GtkBuilder *builder) {
    GtkEntry *entry = GTK_ENTRY(gtk_builder_get_object(builder, entry_name));

    return (gchar*)gtk_entry_get_text(entry);
}
