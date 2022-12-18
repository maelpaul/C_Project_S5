#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "queue.h"

void options(unsigned int tab[], int argc, char *argv[])
{
  int c = 0;
  tab[0] = 10;
  tab[1] = 42;
  for (int i = 0; i < 2; ++i)
  {
    c = getopt(argc, argv, "m:s:");
    if (c == 'm')
      tab[0] = atoi(optarg);
    else if (c == 's')
      tab[1] = atoi(optarg);
  }
}

void world_apply_rule_gol(struct world *w, struct rule *r, unsigned int idx, unsigned int achievement)
{
  if (achievement == 0)
    w->t[idx] = rule_change_to(r, 0);
  else if (achievement == 1)
    w->t[idx] = rule_change_to(r, rand() % rule_num_changes(r));
}

void world_apply_rule_particule(struct world *w, struct rule *r, unsigned int idx)
{
  unsigned int random = rand() % (rule_num_changes(r) - 1);
  w->t[idx] = rule_change_to(r, random);
  int dx = rule_change_dx(r, random);
  int dy = rule_change_dy(r, random);
  unsigned int j = idx % WIDTH;
  unsigned int i = (idx - j) / WIDTH;
  // Getting the coordinates where the particule will go
  unsigned int new_i = (i + dy + HEIGHT) % HEIGHT;
  unsigned int new_j = (j + dx + WIDTH) % WIDTH;
  int new_idx = coord_to_idx(new_i, new_j, WIDTH);

  w->t[new_idx] = rule_change_to(r, rule_num_changes(r) - 1);
}

void world_apply_rule(struct world *w, struct rule *r, unsigned int idx)
{
  if (ACHIEV == 0 || ACHIEV == 1)
    world_apply_rule_gol(w, r, idx, ACHIEV);
  else if (ACHIEV == 2)
    world_apply_rule_particule(w, r, idx);
}

int main(int argc, char *argv[])
{
  unsigned int opts[2] = {};
  options(opts, argc, argv);
  unsigned int nb_frame = opts[0];
  srand(opts[1]);

  struct world w = world_init(1);
  rules_init();

  unsigned int nb_rule = rules_count();

  printf("%d %d\n", WIDTH, HEIGHT);
  world_disp(&w);
  for (unsigned int frame = 0; frame < nb_frame; ++frame)
  {
    struct queue q = queue_init();
    for (int i = 0; i < HEIGHT; ++i)
    {
      for (int j = 0; j < WIDTH; ++j)
      {
        for (unsigned int ith_rule = 0; ith_rule < nb_rule; ++ith_rule)
        {
          struct rule *r = rule_get(ith_rule);
          if (rule_match(&w, r, i, j))
          {
            struct queue_element qe = {r, coord_to_idx(i, j, WIDTH)};
            queue_append(&q, qe);
          }
        }
      }
    }

    for (int i = queue_start(&q); i < queue_end(&q); ++i)
    {
      struct queue_element qe = queue_pop(&q);
      int idx = queue_element_index(qe);
      struct rule *r = queue_element_rule(qe);
      world_apply_rule(&w, r, idx);
    }
    world_disp(&w);
  }
  return 0;
}
