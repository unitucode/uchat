#include "client.h"

/*
 * Function: mx_get_used_power
 * -------------------------------
 * Counts used power to one message
 * 
 * chars: count of characters in message
 * 
 * returns: used power
 */
gdouble mx_get_used_power(guint64 chars) {
    return 0.026751 * chars;
}
