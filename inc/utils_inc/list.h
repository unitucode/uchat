#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct s_node {
    void *data;
    struct s_node *next;
    struct s_node *prev;
}              t_node;

typedef struct s_dl_list {
    size_t size;
    t_node *back;
    t_node *front;
    void (*delete_node)(void **data);
}              t_dl_list;

t_node *mx_push_back(t_dl_list *list, void *data);
t_node *mx_push_front(t_dl_list *list, void *data);
void mx_delete_node(t_dl_list *list, t_node **node);
t_dl_list *mx_new_dl_list(void (*delete_node)(void **data));
t_node *mx_new_node(void *data);
