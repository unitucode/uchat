#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    while (1) {
        printf("------------------server");
        system("leaks -q uchat_server");
        printf("------------------");
        printf("------------------client");
        system("leaks -q uchat");
        printf("------------------");
        sleep(1);
    }
}
