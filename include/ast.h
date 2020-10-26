#ifndef AST_H
#define AST_H

#include "utils.h"

/**
 * Return values for AST functions returning an integer
 */
enum ast_state {
	AST_ERR,
	AST_INVALID_LEN,
	AST_INVALID_TYPE,
	AST_UNIMPLEMENTED,
	AST_NULL_PTR,
	AST_OK = 0,
};


/**
 * Function prototypes for the AST "class" to create a new inherited "class"
 */
typedef struct ast_node *(*ast_node_new_func)(void);
typedef void (*ast_node_del_func)(struct ast_node *);
typedef int (*ast_node_exec_func)(struct ast_node *);

/**
 * Base structure to derive to create new AST nodes. That struct must always be 
 * aggregated in the derived struct, and not as a pointer. It must always be declared as
 * the FIRST member of that derived struct.
 *
 * This way, the base functions for a given AST type will be stored in a "virtual table",
 * which is a static table of function pointers. This will enable the user to always call
 * the same functions, which will then dispatch on the correct implementation for that
 * particular type
 */
struct ast_node {
	const char *type;

	ast_node_new_func new;
	ast_node_del_func del;
	ast_node_exec_func exec;
};

#define AST_NODE_MEMBER_NAME __ast_node
#define AST_NODE_MEMBER struct ast_node AST_NODE_MEMBER_NAME

/**
 * "Upcast" an AST node to its base type, ast_node. This is just a wrapper to avoid
 * typing the cast all the time
 */
#define TO_AST_NODE(__NODE) (&(__NODE)->AST_NODE_MEMBER_NAME)
#define FROM_AST_NODE(__ptr, __type) container_of(__ptr, __type, AST_NODE_MEMBER_NAME)

#define CALL_AST_METHOD(__NODE, __METHOD) ({ \
		struct ast_node *ast_node = TO_AST_NODE(__NODE); \
		ast_node->__METHOD(ast_node); \
	})

#define CALL_AST_NEW(__NODE) CALL_AST_METHOD(__NODE, new)
#define CALL_AST_DEL(__NODE) CALL_AST_METHOD(__NODE, del)
#define CALL_AST_EXEC(__NODE) CALL_AST_METHOD(__NODE, exec)

#endif /* ! AST_H */
