#include "utils.h"

/*
 * Pushs a node to list
 * Set MX_LIST_BACK to index to push in back of list
 * Set list->size to index to push in front of list
 */
void mx_push_node(t_list *list, void *data, size_t index) {
    t_node *current = list->head;
    t_node *tmp = NULL;
    size_t cur_index = 0;

    list->size++;
    if (!index || !current) {
        tmp = mx_new_node(data);
        tmp->next = current;
        list->head = tmp;
        return;
    }
    while (++cur_index < index && current->next)
        current = current->next;
    tmp = mx_new_node(data);
    tmp->next = current->next;
    current->next = tmp;
}

/*
 * Deletes a node from list
 * Set MX_LIST_BACK to index to remove back node from list
 * Set list->size to index to remove front node from list
 */
void mx_remove_node(t_list *list, size_t index) {
    t_node *current = list->head;
    t_node *tmp = NULL;
    size_t cur_index = 0;

    if (!list->size)
        return;
    if (list->size == 1) {
        list->size--;
        free(list->head->data);
        free(list->head);
        list->head = NULL;
        return;
    }
    list->size--;
    while (++cur_index < index && current->next && current->next->next)
        current = current->next;
    tmp = current->next;
    current->next = tmp->next;
    free(tmp->data);
    free(tmp);
}

/*
 * Deletes list of nodes
 */
void mx_delete_list(t_list **list) {
    while ((*list)->size)
        mx_remove_node(*list, MX_LIST_BACK);
    free(*list);
    *list = NULL;
}
