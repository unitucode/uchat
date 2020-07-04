#include "server.h"

/*
 * Function: mx_destroy_date
 * -------------------------------
 * free data
 * 
 * data: dynamically allocated memory gpointer/void*
 */
void mx_destroy_data(gpointer data) {
    g_free(data);
}
