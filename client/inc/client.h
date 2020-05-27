#pragma once

#include "utils.h"
#include <sqlite3.h>
#include <gtk/gtk.h>
#include "protocol.h"

#define MX_GUI_PATH "../src/gui/gui.glade"

typedef struct s_groom {
    GtkListBox *box_rooms;
    GtkScrolledWindow *page;
    GtkListBoxRow *row_room;
    GtkStack *stack_msg;
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
void mx_init_gui(t_chat *chat);
int mx_start_window(t_chat *chat);
void mx_add_room(GtkButton *btn, GtkBuilder *builder);

// gui utils
void mx_scrlldwnd_connect(char *name, GtkWidget *scroll, GtkBuilder *builder);
gchar *mx_get_buffer_text(char *buff_name, GtkBuilder *builder);
void mx_clear_buffer_text(char *buff_name, GtkBuilder *builder);
void mx_widget_switch_visibility(GtkWidget *usr_ctrl, void *widget);
