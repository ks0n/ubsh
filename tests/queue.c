#include <criterion/criterion.h>

#include "queue.h"

Test(queue, push_elements_and_pop_them)
{
	struct queue q;
	queue_init(&q);

	queue_push(&q, (void*)0);
	queue_push(&q, (void*)1);
	queue_push(&q, (void*)2);
	queue_push(&q, (void*)3);

	cr_assert_eq(queue_pop(&q), (void*)0);
	cr_assert_eq(queue_pop(&q), (void*)1);
	cr_assert_eq(queue_pop(&q), (void*)2);
	cr_assert_eq(queue_pop(&q), (void*)3);
}

Test(queue, push_elements_and_at_them)
{
	struct queue q;
	queue_init(&q);

	queue_push(&q, (void*)0);
	queue_push(&q, (void*)1);
	queue_push(&q, (void*)2);
	queue_push(&q, (void*)3);

	cr_assert_eq(queue_at(&q, 0), (void*)0);
	cr_assert_eq(queue_at(&q, 1), (void*)1);
	cr_assert_eq(queue_at(&q, 2), (void*)2);
	cr_assert_eq(queue_at(&q, 3), (void*)3);

	/* Pop to free queue nodes. */
	queue_pop(&q);
	queue_pop(&q);
	queue_pop(&q);
	queue_pop(&q);
}

Test(queue, push_elements_and_peek_them)
{
	struct queue q;
	queue_init(&q);

	queue_push(&q, (void*)0);
	queue_push(&q, (void*)1);
	queue_push(&q, (void*)2);
	queue_push(&q, (void*)3);

	cr_assert_eq(queue_peek_first(&q), (void*)0);
	queue_pop(&q);

	cr_assert_eq(queue_peek_first(&q), (void*)1);
	queue_pop(&q);

	cr_assert_eq(queue_peek_first(&q), (void*)2);
	queue_pop(&q);

	cr_assert_eq(queue_peek_first(&q), (void*)3);
	queue_pop(&q);
}

Test(queue, push_peek_pop_4_times)
{
	struct queue q;
	queue_init(&q);

	queue_push(&q, (void*)0);
	cr_assert_eq(queue_peek_first(&q), (void*)0);
	queue_pop(&q);

	queue_push(&q, (void*)1);
	cr_assert_eq(queue_peek_first(&q), (void*)1);
	queue_pop(&q);

	queue_push(&q, (void*)2);
	cr_assert_eq(queue_peek_first(&q), (void*)2);
	queue_pop(&q);

	queue_push(&q, (void*)3);
	cr_assert_eq(queue_peek_first(&q), (void*)3);
	queue_pop(&q);
}

Test(queue, at_out_of_bounds)
{
	struct queue q;
	queue_init(&q);

	queue_push(&q, (void*)0);
	queue_push(&q, (void*)1);

	cr_assert_eq(queue_at(&q, 0), (void*)0);
	cr_assert_eq(queue_at(&q, 1), (void*)1);
	cr_assert_null(queue_at(&q, 2));

	queue_pop(&q);
	queue_pop(&q);
}

Test(queue, pop_empty)
{
	struct queue q;
	queue_init(&q);

	cr_assert_null(queue_pop(&q));
}

Test(queue, peek_empty)
{
	struct queue q;
	queue_init(&q);

	cr_assert_null(queue_peek_first(&q));
	cr_assert_null(queue_peek_last(&q));
}
