#include <stdio.h>
#include <stdlib.h>

int main(int ac, const char *av[]) {
    if (ac != 2) {
        printf("Usage: ./engine.out [config.xml]\n");
        return EXIT_FAILURE;
    }
    printf("Loading config file: %s\n", av[1]);
    return EXIT_SUCCESS;
}
