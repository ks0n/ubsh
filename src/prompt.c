#include "color.h"
#include "prompt.h"

const char *prompt_get(void)
{
	return MAGENTA("ubsh ") "> ";
}
