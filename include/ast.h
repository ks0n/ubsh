#ifndef AST_H
#define AST_H

/**
 * All possible types of nodes for the AST
 */
enum ast_type {
	AST_NONE = 0,
	AST_VALUE,
	AST_TYPE_LEN, // Amount of types declared for the AST
};

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
	enum ast_type type;
};

/* Functions to define to create a new AST "class" */
typedef struct ast_node *(*ast_node_new_f)(void);
typedef void (*ast_node_del_f)(struct ast_node *);

/**
 * "Upcast" an AST node to its base type, ast_node. This is just a wrapper to avoid
 * typing the cast all the time
 */
#define UPCAST(__NODE) ((struct ast_node *)__NODE)

/**
 * Wrapper to avoid writing the type to define a new AST constructor
 */
#define AST_CONSTRUCTOR(__NAME) struct ast_node *__NAME(void)

/**
 * Wrapper to avoid writing the type to define a new AST destructor
 */
#define AST_DESTRUCTOR(__NAME, __PARAM) void __NAME(struct ast_node *__PARAM)

/**
 * Instanciate a new node for a given AST type
 *
 * @param type Type of the AST node to init
 *
 * @return A generic AST node, instanciated with the proper type
 */
struct ast_node *ast_node_new(enum ast_type type);

/**
 * Release the memory of an instance of an AST node
 *
 * @param node AST Node to free
 * @param type Type of the AST node to free
 *
 * @return AST_OK on success, a negative value form @ast_state on error
 */
int ast_node_del(struct ast_node *node, enum ast_type type);

#endif /* ! AST_H */
