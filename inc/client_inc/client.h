#pragma once

#include "../utils_inc/utils.h"
#include <gtk/gtk.h>

#define MX_GUI_PATH "src/client/gui/gui.glade"

typedef struct s_room {
    GtkListBox *box;
    GtkListBoxRow *row;
}       t_room;

int mx_tcp_connect(const char *host, const char *serv);

//gui
int mx_window_main(int argc, char **argv);
void mx_add_room(GtkButton *btn, GtkBuilder *builder);

// gui utils
void mx_scrlldwnd_connect(char *wnd_name, GtkBuilder *builder);
gchar *mx_get_buffer_text(char *buff_name, GtkBuilder *builder);
void mx_widget_switch_visibility(void *usr_ctrl, void *widget);
