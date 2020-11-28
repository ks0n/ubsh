#include "command.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#include "logger.h"

int command_execute(int argc, char *const *argv)
{
	(void)argc;
	char *prog = argv[0];

	pid_t ret;
	int wstatus;

	pid_t child_pid = fork();
	if (!child_pid) {
		execvp(prog, argv);
		LOG(LOG_ERR, "[child] failed to exec \"%s\"", prog);
		exit(1);
	} else if (child_pid < 0) {
		return -1;
	}

	// Parent

	do {
		ret = waitpid(child_pid, &wstatus, 0);
		if (ret == -1) {
			warn("waitpid");
			return -1;
		}
	} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));

	return WEXITSTATUS(wstatus);
}
