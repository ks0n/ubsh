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
	struct queue_node *head;
	struct queue_node *tail;
	size_t len;
};

void queue_init(struct queue *q);
size_t queue_len(const struct queue *q);
bool queue_is_empty(const struct queue *q);

int queue_push(struct queue *q, void *data);
void *queue_pop(struct queue *q);
void *queue_at(struct queue *q, size_t idx);

/* Peek element inserted the longest time ago. */
void *queue_peek(struct queue *q);

/* Peek element inserted the most recently. */
void *queue_peek_head(struct queue *q);

#endif /* ! QUEUE_H */
