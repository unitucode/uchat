#include "client.h"

void mx_text_buffer_set_tags(GtkTextBuffer *buffer) {
    gtk_text_buffer_create_tag(buffer, MX_FT_SCRATCH, "strikethrough", true, NULL);
    gtk_text_buffer_create_tag(buffer, MX_FT_BOLD, "weight", PANGO_WEIGHT_BOLD, NULL);
    gtk_text_buffer_create_tag(buffer, MX_FT_IMPORTANT, "background", "rgba(255, 105, 140, 0.5)", NULL);
    gtk_text_buffer_create_tag(buffer, MX_FT_ITALIC, "style", PANGO_STYLE_ITALIC, NULL);
    gtk_text_buffer_create_tag(buffer, MX_FT_UNDER, "underline", PANGO_UNDERLINE_LOW, NULL);
}

static void set_tags(GtkTextBuffer *buffer, gchar *ft_chars) {
    GtkTextIter start;
    GtkTextIter end;
    gchar *text = NULL;

    gtk_text_buffer_get_iter_at_offset(buffer, &start, 0);
    gtk_text_buffer_get_iter_at_offset(buffer, &end, gtk_text_buffer_get_char_count(buffer));
    text = gtk_text_buffer_get_text(buffer, &start, &end, TRUE);
    gtk_text_buffer_get_iter_at_offset(buffer, &start, g_strrstr(text, ft_chars) - text + strlen(ft_chars));
    g_print("start = %d\n", gtk_text_iter_get_offset(&start));
    gtk_text_buffer_get_iter_at_offset(buffer, &end, g_strrstr(text + gtk_text_iter_get_offset(&start), ft_chars) - text);
    g_print("end = %d\n", gtk_text_iter_get_offset(&end));
    gtk_text_buffer_apply_tag_by_name(buffer, ft_chars, &start, &end);
}

void mx_format_text(GtkTextBuffer *buffer) {
    GtkTextIter start;
    GtkTextIter end;

    gtk_text_buffer_get_iter_at_offset(buffer, &start, 0);
    gtk_text_buffer_get_iter_at_offset(buffer, &end, gtk_text_buffer_get_char_count(buffer));
    gtk_text_buffer_remove_all_tags(buffer, &start, &end);
    set_tags(buffer, MX_FT_UNDER);
}



