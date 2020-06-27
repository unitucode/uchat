#include "client.h"

void mx_css_connect() {
    GtkCssProvider *cssProv;

    cssProv = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProv,
                                    "../src/gui/resources/light-theme.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProv),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
}
