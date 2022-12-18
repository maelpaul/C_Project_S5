#include <stdio.h>
#include <stdlib.h>
#include "worldalgo.h"

int coord_to_idx(unsigned int i, unsigned int j, unsigned int w)
{
  return w * i + j;
}

enum color color_cell(unsigned int achievement)
{
  int random = rand() % 4;
  if (achievement == 0)
    return (random == 0) ? WHITE : BLACK;
  else if (achievement == 1)
    return (random == 0) ? NEUTRAL : BLACK;
  else if (achievement == 2)
    return (random == 0) ? YELLOW : BLACK;
  else
    return BLACK;
}

struct world world_init_gol(int fill, unsigned int achievement)
{
  enum color colors[4] = {WHITE, RED, BLUE, GREEN};
  struct world w = {};
  if (fill)
  {
    for (int i = 0; i < HEIGHT * WIDTH; ++i)
    {
      if (achievement == 0)
        w.t[i] = color_cell(0);
      else if (achievement == 1)
        w.t[i] = (color_cell(1) == NEUTRAL) ? colors[rand() % 4] : BLACK;
    }
  }
  return w;
}

struct world world_init_particule(int fill)
{
  struct world w = {};
  if (fill)
  {
    for (int i = 0; i < HEIGHT * WIDTH; ++i)
    {
      w.t[i] = color_cell(2);
    }
    // Setting the bottom of the world as rock
    for (int i = (HEIGHT - 1) * WIDTH; i < HEIGHT * WIDTH; ++i)
    {
      w.t[i] = GREY;
    }
    if (WIDTH * HEIGHT >= 1200)
    {
      // Adding holes at the bottom and stairs to demonstrate the sliding of the sand
      w.t[216] = GREY;
      w.t[257] = GREY;
      w.t[298] = GREY;
      w.t[299] = GREY;
      w.t[340] = GREY;
      w.t[381] = GREY;
      w.t[622] = GREY;
      w.t[1022] = GREY;
      w.t[983] = GREY;
      w.t[944] = GREY;
      // Creating stairs
      w.t[712] = GREY;
      w.t[751] = GREY;
      w.t[753] = GREY;
      w.t[805] = GREY;
      w.t[806] = GREY;
      w.t[807] = GREY;
      w.t[1165] = BLACK;
      w.t[1166] = BLACK;
      w.t[1167] = BLACK;
      w.t[1180] = BLACK;
      w.t[1181] = BLACK;
      w.t[1182] = BLACK;
      w.t[1191] = BLACK;
      w.t[1192] = BLACK;
      w.t[1193] = BLACK;
    }
  }
  return w;
}

struct world world_init(int fill)
{
  if (ACHIEV == 0 || ACHIEV == 1)
    return world_init_gol(fill, ACHIEV);
  else if (ACHIEV == 2)
    return world_init_particule(fill);
}

void world_disp(struct world *w)
{
  printf("#\n");
  for (int i = 0; i < HEIGHT; ++i)
  {
    for (int j = 0; j < WIDTH; ++j)
    {
      printf("%d ", w->t[coord_to_idx(i, j, WIDTH)]);
    }
    printf("\n");
  }
}