#include "server.h"

void mx_destroy_data(gpointer data) {
    g_free(data);
}
