#include <stdio.h>
#include <stdlib.h>
#include "../src/queue.h"

void test_queue()
{
	struct queue q = queue_init();
	struct queue_element qe0 = {rule_get(0), 42};
	struct queue_element qe1 = {rule_get(1), 678};
	struct queue_element qe2 = {rule_get(2), 420};
	printf("start: %d, end: %d\n", queue_start(&q), queue_end(&q));
	queue_append(&q, qe0);
	printf("start: %d, end: %d\n", queue_start(&q), queue_end(&q));
	queue_append(&q, qe1);
	printf("start: %d, end: %d\n", queue_start(&q), queue_end(&q));
	queue_append(&q, qe2);
	printf("start: %d, end: %d\n", queue_start(&q), queue_end(&q));

	printf("FIFO : %d\n", (qe0.index == queue_pop(&q).index));
	printf("start: %d, end: %d\n", queue_start(&q), queue_end(&q));

	printf("FIFO : %d\n", (qe1.index == queue_pop(&q).index));
	printf("start: %d, end: %d\n", queue_start(&q), queue_end(&q));

	printf("FIFO : %d\n", (qe2.index == queue_pop(&q).index));
	printf("start: %d, end: %d\n", queue_start(&q), queue_end(&q));
	reset_queue(&q);
	printf("start: %d, end: %d\n", queue_start(&q), queue_end(&q));

	struct queue_element qe = {};
	for (int i = 0; i < 1500; ++i)
		queue_append(&q, qe0);

	printf("start: %d, end: %d\n", queue_start(&q), queue_end(&q));
	for (int i = 0; i < 1500; ++i)
		qe = queue_pop(&q);

	printf("FIFO : %d\n", (qe.index == qe0.index));
	printf("start: %d, end: %d\n", queue_start(&q), queue_end(&q));
}

void test_world()
{
	double somme = 0;
	for (int i = 0; i < 10; ++i)
	{
		struct world w = world_init(1);
		for (int j = 0; j < HEIGHT * WIDTH; ++j)
		{
			if (w.t[j] != 0)
				++somme;
		}
	}
	printf("Proportion de cellules vivantes : %f\n", somme / (HEIGHT * WIDTH * 10));
}

int main(void)
{
	rules_init();
	test_queue();
	test_world();
	return 0;
}