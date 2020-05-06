#include "utils.h"

/*
 * Creates new node of list
 */
t_node *mx_new_node(void *data) {
    t_node *new_node = mx_malloc(sizeof(t_node));

    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}
