#pragma once

#include "utils.h"
#include <sqlite3.h>
#include <gtk/gtk.h>

#define MX_GUI_PATH "../src/gui/gui.glade"

typedef struct s_groom {
    GtkListBox *box;
    GtkListBoxRow *row;
}       t_groom;

typedef struct s_chat {
    SSL *ssl;
    GtkBuilder *builder;
}              t_chat;

int mx_tcp_connect(const char *host, const char *serv);
t_chat *mx_init_chat(void);
void mx_signup(SSL *ssl);
void mx_login(SSL *ssl);

//gui
GtkBuilder *mx_init_window(int argc, char **argv);
int mx_start_window(t_chat *chat);
void mx_add_room(GtkButton *btn, GtkBuilder *builder);

// gui utils
void mx_scrlldwnd_connect(char *wnd_name, GtkBuilder *builder);
gchar *mx_get_buffer_text(char *buff_name, GtkBuilder *builder);
void mx_widget_switch_visibility(void *usr_ctrl, void *widget);
