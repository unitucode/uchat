#include "client.h"

int main(int argc, char **argv) {
    argc++;
    argv++;
    t_list *list = mx_new_list();

    mx_push_node(list, strdup("hello1"), 0);
    mx_push_node(list, strdup("hello2"), 0);
    printf("size = %zu\n", list->size);
    for (t_node *node = list->head; node; node = node->next) {
        fprintf(stderr, "%s\n", node->data);
    }
    fprintf(stderr, "test\n");
    mx_delete_list(&list);
    system("leaks -q uchat");
}
