#include "queue.h"

void queue_init(struct queue *q)
{
	q->last = NULL;
	q->first = NULL;
	q->len = 0;
}

size_t queue_len(const struct queue *q)
{
	return q->len;
}

bool queue_is_empty(const struct queue *q)
{
	return queue_len(q) == 0;
}

int queue_push(struct queue *q, void *data)
{
	struct queue_node *node = malloc(sizeof(*node));
	if (!node)
		return -1;

	node->data = data;
	node->prev = NULL;
	node->next = q->last;

	if (node->next)
		node->next->prev = node;

	q->last = node;

	if (queue_is_empty(q))
		q->first = node;

	q->len++;

	return 0;
}

void *queue_peek_first(struct queue *q)
{
	if (queue_is_empty(q))
		return NULL;

	return q->first->data;
}

void *queue_peek_last(struct queue *q)
{
	if (queue_is_empty(q))
		return NULL;

	return q->last->data;
}

void *queue_pop(struct queue *q)
{
	struct queue_node *first_node;
	void *data;

	if (queue_is_empty(q))
		return NULL;

	first_node = q->first;
	data = first_node->data;

	q->first = q->first->prev;
	q->len--;

	if (queue_is_empty(q))
		q->last = NULL;

	free(first_node);

	return data;
}

void *queue_at(struct queue *q, size_t idx)
{
	struct queue_node *node;

	if (idx >= queue_len(q))
		return NULL;

	node = q->first;

	for (size_t i = 0; i < idx; i++)
		node = node->prev;

	return node->data;
}
