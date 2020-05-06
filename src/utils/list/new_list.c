#include "utils.h"

/*
 * Creates new list of nodes
 */
t_list *mx_new_list() {
    t_list *new_list = mx_malloc(sizeof(t_list));

    new_list->head = NULL;
    new_list->size = 0;
    return new_list;
}
