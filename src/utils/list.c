#include "utils.h"

/*
 * Pushs a node to list
 * Use MX_LIST_BACK to push in back of list
 * Use list->size to push in front of list
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
 * Use MX_LIST_BACK to remove back node from list
 * Use list->size to remove front node from list
 */
void mx_remove_node(t_list *list, size_t index) {
    t_node *current = list->head;
    t_node *tmp = NULL;
    size_t cur_index = 0;

    if (!list->size)
        return;
    list->size--;
    if (!index) {
        tmp = list->head->next;
        free(list->head->data);
        free(list->head);
        list->head = tmp;
        return;
    }
    while (++cur_index < index && current->next && current->next->next)
        current = current->next;
    tmp = current->next;
    current->next = tmp->next;
    free(tmp->data);
    free(tmp);
}

/*
 * Creates new node of list
 */
t_node *mx_new_node(void *data) {
    t_node *new_node = mx_malloc(sizeof(t_node));

    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

/*
 * Creates new list of nodes
 */
t_list *mx_new_list() {
    t_list *new_list = mx_malloc(sizeof(t_list));

    new_list->head = NULL;
    new_list->size = 0;
    return new_list;
}
