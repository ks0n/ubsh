#include <stdlib.h>
#include <stdio.h>

#include "linenoise/linenoise.h"

#include "prompt.h"

int main(void) {
    char *line = NULL;

    while ((line = linenoise(prompt_get()))) {
        printf("input: %s\n", line);

        linenoiseFree(line);
    }

    return 0;
}
