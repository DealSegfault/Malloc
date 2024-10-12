#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
void print(char *s) {
    write(1, s, strlen(s));
}

// void free(void *ptr) {
//     printf("Custom free called with ptr: %p\n", ptr);
//     // Rest of your code
// }

// void  *realloc(void *ptr, size_t size) {
//     printf("Custom realloc called with ptr: %p, size: %zu\n", ptr, size);
//     // Rest of your code
// }

int main() {
    char *addr;

    addr = malloc(16);
    free(NULL);
    free((void *)addr + 5);
    if (realloc((void *)addr + 5, 10) == NULL)
        print("Bonjour\n");
}

