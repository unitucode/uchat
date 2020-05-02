#include "client.h"

int main(int argc, char **argv) {
    argc++;
    argv++;
    t_list *list = mx_new_list();

    mx_push_node(list, strdup("hello1"), 0);
    printf("size = %zu\n", list->size);
    mx_push_node(list, strdup("hello2"), 0);
    printf("size = %zu\n", list->size);
    mx_push_node(list, strdup("hello3"), 0);
    printf("size = %zu\n", list->size);
    mx_remove_node(list, 2);
    printf("size = %zu\n", list->size);
    mx_push_node(list, strdup("hello4"), 1);
    printf("size = %zu\n", list->size);
    for (t_node *node = list->head; node; node = node->next) {
        fprintf(stderr, "%s\n", node->data);
    }
    fprintf(stderr, "test\n");
    system("leaks -q uchat");
}
