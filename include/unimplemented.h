#ifndef UNIMPLEMENTED_H
#define UNIMPLEMENTED_H

#include <err.h>
#include <stdlib.h>

#define UNIMPLEMENTED()  \
	errx(EXIT_FAILURE, "function %s in %s:%d not implemented", __FUNCTION__, __FILE__, __LINE__)

#endif /* ! UNIMPLEMENTED_H */
