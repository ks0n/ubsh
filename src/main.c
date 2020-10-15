#include <stdlib.h>
#include <stdio.h>

#include "linenoise/linenoise.h"

int main(void) {
    char *line = NULL;

    while ((line = linenoise("> "))) {
        printf("input: %s\n", line);

        linenoiseFree(line);
    }

    return 0;
}
