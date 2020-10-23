#include "queue.h"

void queue_init(struct queue *q)
{
	q->head = NULL;
	q->tail = NULL;
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
	node->next = q->head;

	if (node->next)
		node->next->prev = node;

	q->head = node;

	if (queue_is_empty(q))
		q->tail = node;

	q->len++;

	return 0;
}

void *queue_peek(struct queue *q)
{
	if (queue_is_empty(q))
		return NULL;

	return q->tail->data;
}

void *queue_pop(struct queue *q)
{
	struct queue_node *tail_node;
	void *data;

	if (queue_is_empty(q))
		return NULL;

	tail_node = q->tail;
	data = tail_node->data;

	q->tail = q->tail->prev;
	q->len--;

	if (queue_is_empty(q))
		q->head = NULL;

	free(tail_node);

	return data;
}

void *queue_at(struct queue *q, size_t idx)
{
	struct queue_node *node;

	if (idx >= queue_len(q))
		return NULL;

	node = q->tail;

	for (size_t i = 0; i < idx; i++)
		node = node->prev;

	return node->data;
}
