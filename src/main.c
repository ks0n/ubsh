#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <readline/readline.h>

#include "prompt.h"
#include "charstream.h"
#include "lexer.h"

int main(void)
{
	char *line = NULL;
	size_t line_len;

	while ((line = readline(prompt_get()))) {
		line_len = strlen(line);

		if (!line || !line_len)
			continue;

		struct lexer lexer;
		const struct token *tok = NULL;
		FILE *file = fmemopen(line, line_len, "r");
		lexer_init(&lexer, file);

		printf("tokens:\n");

		while (1) {
			tok = lexer_consume(&lexer);
			if (!tok || token_is_eof(tok))
				break;

			printf("- \"%s\", type: %i\n", token_characters(tok),
			       token_type(tok));
		}

		puts("");
		fclose(file);

		lexer_cleanup(&lexer);
		free(line);
	}

	return 0;
}
