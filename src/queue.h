#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "worldalgo.h"
#include "rule.h"

#define WORLD_SIZE WIDTH *HEIGHT

struct queue_element
{
  struct rule *r;
  unsigned int index;
};

struct queue
{
  int start;
  int end;
  struct queue_element tab[WORLD_SIZE];
};

// Function used to get the start of the queue
int queue_start(const struct queue *q);

// Function used to get the end of the queue (first empty element)
int queue_end(const struct queue *q);

// Function initializing an empty queue
struct queue queue_init();

// Function used to add an element in the queue
void queue_append(struct queue *q, const struct queue_element qe);

// Function used to remove an element of the queue
struct queue_element queue_pop(struct queue *q);

// Function used to reset the queue
void reset_queue(struct queue *q);

// Function used to get the index of an element 
int queue_element_index(struct queue_element qe);

// Function used to get the pointer on the rule of an element
struct rule *queue_element_rule(struct queue_element qe);

#endif // __QUEUE_H__
