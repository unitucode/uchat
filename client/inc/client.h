#pragma once

#include "utils.h"
#include "protocol.h"
#include "sqlite3.h"
#include <gtk/gtk.h>
#include <glib.h>
#include <gio/gio.h>

#define MX_GUI_PATH "../src/gui/gui.glade"

typedef struct s_groom {
    GtkListBox *box;
    GtkListBoxRow *row;
}       t_groom;

typedef struct s_chat {
    char *auth_token;
    SSL *ssl;
    GtkBuilder *builder;
    bool (*request_handler[RQ_COUNT_REQUEST])(t_dtp *dtp, struct s_chat *chat);
}              t_chat;


t_dtp *mx_recv(GInputStream *in);
gssize mx_send(GOutputStream *out, t_dtp *dtp);
int mx_tcp_connect(const char *host, const char *serv);
t_chat *mx_init_chat(void);
bool mx_authorization(t_dtp *token, t_chat *chat);
bool mx_error_handle(t_dtp *data, t_chat *chat);
void mx_signup(SSL *ssl);
void mx_login(SSL *ssl);
void *mx_receiver(void *arg);
void mx_init_receiver(t_chat *chat);

//gui
GtkBuilder *mx_init_window(int argc, char **argv);
int mx_start_window(t_chat *chat);
void mx_add_room(GtkButton *btn, GtkBuilder *builder);

// gui utils
void mx_scrlldwnd_connect(char *wnd_name, GtkBuilder *builder);
gchar *mx_get_buffer_text(char *buff_name, GtkBuilder *builder);
void mx_widget_switch_visibility(void *usr_ctrl, void *widget);
