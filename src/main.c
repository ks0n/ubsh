#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linenoise/linenoise.h"

#include "prompt.h"
#include "charstream.h"

int main(void)
{
	char *line = NULL;

	while ((line = linenoise(prompt_get()))) {
		struct charstream stream;
		FILE *file = fmemopen(line, strlen(line), "r");
		charstream_init(&stream, file);

		printf("input: ");
		while (1) {
			char c = charstream_read(&stream);
			if (c == CHARSTREAM_EOF || c == CHARSTREAM_ERR)
				break;

			fputc(c, stdout);
		}

		putc('\n', stdout);
		fclose(file);

		linenoiseFree(line);
	}

	return 0;
}
