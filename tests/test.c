// test.c
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // Include the string header for strncat and strlen

// Declare the show_alloc_mem function
void show_alloc_mem(void);

int main() {
    char *ptr1;
    char *ptr2;

    ptr1 = malloc(42);
    if (!ptr1) {
        perror("malloc");
        return 1;
    }
    snprintf(ptr1, 42, "Hello, World!");
    printf("ptr1: %s\n", ptr1);

    ptr2 = malloc(84);
    if (!ptr2) {
        perror("malloc");
        free(ptr1);
        return 1;
    }
    snprintf(ptr2, 84, "Custom malloc testing.");
    printf("ptr2: %s\n", ptr2);

    show_alloc_mem();

    ptr1 = realloc(ptr1, 100);
    if (!ptr1) {
        perror("realloc");
        free(ptr2);
        return 1;
    }
    strncat(ptr1, " Extended.", 100 - strlen(ptr1) - 1);
    printf("ptr1 after realloc: %s\n", ptr1);

    show_alloc_mem();

    free(ptr1);
    free(ptr2);

    show_alloc_mem();

    return 0;
}
