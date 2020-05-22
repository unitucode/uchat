#pragma once

#include "utils.h"
#include <sqlite3.h>
#include <gtk/gtk.h>

#define MX_GUI_PATH "src/client/gui/gui.glade"

typedef struct s_groom {
    GtkListBox *box_rooms;
    GtkListBox *box_msg;
    GtkListBoxRow *row_room;
    GtkStack *stack_msg;
}       t_groom;

int mx_tcp_connect(const char *host, const char *serv);
void mx_signup(SSL *ssl);
void mx_login(SSL *ssl);

//gui
int mx_window_main(int argc, char **argv);

// gui utils
void mx_scrlldwnd_connect(char *wnd_name, GtkBuilder *builder);
gchar *mx_get_buffer_text(char *buff_name, GtkBuilder *builder);
void mx_widget_switch_visibility(GtkWidget *usr_ctrl, void *widget);
