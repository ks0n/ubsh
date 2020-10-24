#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdbool.h>

struct queue_node {
	void *data;
	struct queue_node *prev;
	struct queue_node *next;
};

struct queue {
	struct queue_node *first;
	struct queue_node *last;
	size_t len;
};

void queue_init(struct queue *q);
size_t queue_len(const struct queue *q);
bool queue_is_empty(const struct queue *q);

int queue_push(struct queue *q, void *data);
void *queue_pop(struct queue *q);
void *queue_at(struct queue *q, size_t idx);

/* Peek the element that will be popped first. */
void *queue_peek_first(struct queue *q);

/* Peek the element that will be popped last . */
void *queue_peek_last(struct queue *q);

#endif /* ! QUEUE_H */
