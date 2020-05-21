#include "utils.h"
#include "list.h"

/*
 * Pushs a node to list
 * Set MX_LIST_BACK to index to push in back of list
 * Set list->size to index to push in front of list
 */
t_node *mx_push_back(t_dl_list *list, void *data) {
    t_node *new_node = mx_new_node(data);

    if (list->back)
        list->back->prev = new_node;
    else
        list->front = new_node;
    new_node->next = list->back;
    list->back = new_node;
    list->size++;
    return new_node;
}

t_node *mx_push_front(t_dl_list *list, void *data) {
    t_node *new_node = mx_new_node(data);

    if (list->front)
        list->front->next = new_node;
    else
        list->back = new_node;
    new_node->prev = list->front;
    list->front = new_node;
    list->size++;
    return new_node;
}

/*
 * Deletes a node from list
 * Set MX_LIST_BACK to index to remove back node from list
 * Set list->size to index to remove front node from list
 */
void mx_delete_node(t_dl_list *list, t_node **node) {
    t_node *del_node = *node;

    if (del_node->prev)
        del_node->prev->next = del_node->next;
    else
        list->back = del_node->next;
    if (del_node->next)
        del_node->next->prev = del_node->prev;
    else
        list->front = del_node->prev;
    list->delete_node(&del_node->data);
    list->size--;
    *node = NULL;
    free(*node);
}
