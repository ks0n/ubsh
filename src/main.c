#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <readline/readline.h>

#include "prompt.h"
#include "logger.h"
#include "charstream.h"
#include "lexer.h"
#include "ast/ast.h"
#include "ast/parser.h"

int main(void)
{
	char *line = NULL;
	size_t line_len;
	LOG(LOG_INFO, "ubsh started");
	LOG(LOG_WARN, "ubsh is not a true shell yet!");
	LOG(LOG_ERR, "we're using readline");

	while ((line = readline(prompt_get()))) {
		line_len = strlen(line);

		if (!line || !line_len)
			continue;

		struct lexer lexer;
		FILE *file = fmemopen(line, line_len, "r");
		lexer_init(&lexer, file);

		struct ast_node *root = NULL;
		if (parser_parse(&root, &lexer) < 0) {
			LOG(LOG_ERR, "failed to parse input");
			goto cleanup;
		}

		int exit_code = root->exec(root);

		printf("$? %d\n", exit_code);

		puts("");

	cleanup:
		if (root)
			root->del(root);
		lexer_cleanup(&lexer);
		fclose(file);
		free(line);
	}

	return 0;
}
