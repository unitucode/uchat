#include "utils.h"
#include "list.h"

/*
 * Creates new list of nodes
 */
t_dl_list *mx_new_dl_list(void (*delete_node)(void **data)) {
    t_dl_list *list = mx_malloc(sizeof(t_dl_list));

    list->delete_node = delete_node;
    list->size = 0;
    list->back = NULL;
    list->front = NULL;
    return list;
}
