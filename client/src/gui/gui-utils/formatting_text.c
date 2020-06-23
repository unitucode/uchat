#include "client.h"

void mx_text_buffer_set_tags(GtkTextBuffer *buffer) {
    gtk_text_buffer_create_tag(buffer, MX_FT_SCRATCH, "strikethrough", true, NULL);
    gtk_text_buffer_create_tag(buffer, MX_FT_BOLD, "weight", PANGO_WEIGHT_BOLD, NULL);
    gtk_text_buffer_create_tag(buffer, MX_FT_IMPORTANT, "background", "rgba(255, 105, 140, 0.5)", NULL);
    gtk_text_buffer_create_tag(buffer, MX_FT_ITALIC, "style", PANGO_STYLE_ITALIC, NULL);
    gtk_text_buffer_create_tag(buffer, MX_FT_UNDER, "underline", PANGO_UNDERLINE_LOW, NULL);
}

static void set_tags(GtkTextBuffer *buffer, gchar *ft_chars) {
    // GtkTextIter start;
    // GtkTextIter end;
    // gchar *text = NULL;
    // gint start_offset = 0;

    // gtk_text_buffer_get_iter_at_offset(buffer, &start, 0);
    // gtk_text_buffer_get_iter_at_offset(buffer, &end, gtk_text_buffer_get_char_count(buffer));
    // text = gtk_text_buffer_get_text(buffer, &start, &end, TRUE);
    // while ((unsigned long)(text - save) <= strlen(save) && g_strstr_len(text, strlen(text), ft_chars)) {
    //     gtk_text_buffer_get_iter_at_offset(buffer, &start, g_strstr_len(text, strlen(text), ft_chars) - text + strlen(ft_chars));
    //     start_offset = gtk_text_iter_get_offset(&start);
    //     gtk_text_buffer_get_iter_at_offset(buffer, &end, g_strstr_len(text + start_offset, strlen(text + start_offset), ft_chars) - text);
    //     gtk_text_buffer_apply_tag_by_name(buffer, ft_chars, &start, &end);
    //     gtk_text_iter_set_offset(&start, 0);
    //     gtk_text_iter_set_offset(&end, gtk_text_buffer_get_char_count(buffer));
    //     text = gtk_text_buffer_get_text(buffer, &start, &end, TRUE);
    // }
    // GtkTextIter start;
    // GtkTextIter end;
    // gchar *text = NULL;
    // gchar *sub = NULL;

    // gtk_text_buffer_get_iter_at_offset(buffer, &start, 0);
    // gtk_text_buffer_get_iter_at_offset(buffer, &end, gtk_text_buffer_get_char_count(buffer));
    // text = gtk_text_buffer_get_text(buffer, &start, &end, TRUE);
    // while ((sub = g_strstr_len(text, strlen(text), ft_chars))) {
    //     gtk_text_iter_set_offset(&start, sub - text);
    //     gtk_text_iter_set_offset(&end, sub - text + strlen(ft_chars));
    //     gtk_text_buffer_delete(buffer, &start, &end);
    //     text = gtk_text_buffer_get_text(buffer, &start, &end, TRUE);
    //     sub = g_strstr_len(text, strlen(text), ft_chars);
    //     gtk_text_iter_set_offset(&end, sub - text);
    //     gtk_text_buffer_apply_tag_by_name(buffer, ft_chars, &start, &end);
    //     gtk_text_iter_set_offset(&start, sub - text);
    //     gtk_text_iter_set_offset(&end, sub - text + strlen(ft_chars));
    //     gtk_text_buffer_delete(buffer, &start, &end);
    //     gtk_text_iter_set_offset(&start, 0);
    //     gtk_text_iter_set_offset(&end, gtk_text_buffer_get_char_count(buffer));
    //     text = gtk_text_buffer_get_text(buffer, &start, &end, TRUE);
    // }
    (void)buffer;
    (void)ft_chars;
}

void mx_format_text(GtkTextBuffer *buffer) {
    GtkTextIter start;
    GtkTextIter end;

    gtk_text_buffer_get_iter_at_offset(buffer, &start, 0);
    gtk_text_buffer_get_iter_at_offset(buffer, &end, gtk_text_buffer_get_char_count(buffer));
    gtk_text_buffer_remove_all_tags(buffer, &start, &end);
    set_tags(buffer, MX_FT_IMPORTANT);
    set_tags(buffer, MX_FT_ITALIC);
    set_tags(buffer, MX_FT_UNDER);
    set_tags(buffer, MX_FT_SCRATCH);
    set_tags(buffer, MX_FT_BOLD);
}



