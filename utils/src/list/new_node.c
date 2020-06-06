#include "utils.h"
#include "list.h"

/*
 * Creates new node of list
 */
t_node *mx_new_node(void *data) {
    t_node *node = mx_malloc(sizeof(t_node));

    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}
