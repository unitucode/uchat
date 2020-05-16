#pragma once

#include "../utils_inc/utils.h"
#define MX_GUI_PATH "src/client/gui/gui.glade"
int mx_tcp_connect(const char *host, const char *serv);

//gui
int mx_window_main(int argc, char **argv);
void mx_add_room(GtkButton *btn, GtkBuilder *builder);
