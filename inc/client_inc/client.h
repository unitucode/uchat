#pragma once

#include "utils.h"
#include <sqlite3.h>
#include <gtk/gtk.h>

#define MX_GUI_PATH "src/client/gui/gui.glade"

typedef struct s_lbroom {
    GtkListBox *box;
    GtkListBoxRow *row;
}       t_lbroom;

int mx_tcp_connect(const char *host, const char *serv);
void mx_signup(SSL *ssl);
void mx_login(SSL *ssl);

//gui
int mx_window_main(int argc, char **argv);
void mx_add_room(GtkButton *btn, GtkBuilder *builder);

// gui utils
void mx_scrlldwnd_connect(char *wnd_name, GtkBuilder *builder);
gchar *mx_get_buffer_text(char *buff_name, GtkBuilder *builder);
void mx_widget_switch_visibility(void *usr_ctrl, void *widget);
