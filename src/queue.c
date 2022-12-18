#include <stdio.h>
#include "queue.h"

int queue_start(const struct queue *q)
{
  return (*q).start;
}

int queue_end(const struct queue *q)
{
  return (*q).end;
}

struct queue queue_init()
{
  struct queue q = {};
  return q;
}

void queue_append(struct queue *q, struct queue_element qe)
{
  int e = queue_end(q);
  if (e < WORLD_SIZE)
  {
    (*q).tab[e] = qe;
    (*q).end = e + 1;
  }
}

struct queue_element queue_pop(struct queue *q)
{
  int s = queue_start(q);
  int e = queue_end(q);
  struct queue_element qe = (*q).tab[s];
  struct queue_element empty = {};
  if (s >= e)
  {
    return empty;
  }
  (*q).start = s + 1;
  return qe;
}

void reset_queue(struct queue *q)
{
  (*q).start = 0;
  (*q).end = 0;
}

int queue_element_index(struct queue_element qe)
{
  return qe.index;
}

struct rule *queue_element_rule(struct queue_element qe)
{
  return qe.r;
}