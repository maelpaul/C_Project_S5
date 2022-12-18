#include <stdio.h>
#include <stdlib.h>
#include "worldalgo.h"
#include "rule.h"

#define NB_RULE 6

#define LENGTH_PATTERN 9
#define MAX_NB_TRANSFORMATION 5

struct rule
{
  unsigned int pattern[LENGTH_PATTERN];
  int nb_neighbour; // Only for game of life : number of neighbour
  int nb_transformation;
  int transformation[MAX_NB_TRANSFORMATION];
  int dx[MAX_NB_TRANSFORMATION]; // Only for sand
  int dy[MAX_NB_TRANSFORMATION]; // Only for sand
};

static struct rule rules[NB_RULE];

void array_cpy(int len, unsigned int dst[], const unsigned int src[])
{
  for (int i = 0; i < len; ++i)
    dst[i] = src[i];
}

int array_cmp(int len, unsigned int const array1[], unsigned int const array2[])
{
  int i = 0;
  while (i < len)
  {
    if (array1[i] != array2[i])
      return 0;
    ++i;
  }
  return 1;
}

int nb_color_match(int len, unsigned int val[], unsigned int color)
{
  int nb_match = 0;
  for (int i = 0; i < len; ++i)
  {
    if (val[i] == color && i != 4)
      ++nb_match;
  }
  return nb_match;
}

void set_transformation(int transformations[], enum color col_central_cell, int nb_match)
{
  if ((col_central_cell == BLACK && nb_match == 3) || (col_central_cell == NEUTRAL && (nb_match == 2 || nb_match == 3)))
  {
    transformations[0] = WHITE;
    transformations[1] = RED;
    transformations[2] = BLUE;
    transformations[3] = GREEN;
  }
  else
  {
    transformations[0] = BLACK;
    transformations[1] = BLACK;
    transformations[2] = BLACK;
    transformations[3] = BLACK;
  }
}

void rules_init_gol()
{
  // Game of life using patterns
  for (int i = 0; i < NB_RULE; ++i)
  {
    unsigned int bits[9] = {};
    bits[0] = (i % 2) * NEUTRAL;
    bits[1] = ((i / 2) % 2) * NEUTRAL;
    bits[2] = ((i / 4) % 2) * NEUTRAL;
    bits[3] = ((i / 8) % 2) * NEUTRAL;
    bits[4] = ((i / 16) % 2) * NEUTRAL;
    bits[5] = ((i / 32) % 2) * NEUTRAL;
    bits[6] = ((i / 64) % 2) * NEUTRAL;
    bits[7] = ((i / 128) % 2) * NEUTRAL;
    bits[8] = ((i / 256) % 2) * NEUTRAL;

    rules[i].nb_neighbour = nb_color_match(LENGTH_PATTERN, bits, NEUTRAL);

    array_cpy(LENGTH_PATTERN, rules[i].pattern, bits);

    rules[i].nb_transformation = 4;

    set_transformation(rules[i].transformation, bits[4], rules[i].nb_neighbour);
  }
}

void rules_init_particule()
{
  // Rule for the sand when it's empty underneath
  unsigned int pattern0[9] = {NEUTRAL, NEUTRAL, NEUTRAL,
                              NEUTRAL, YELLOW, NEUTRAL,
                              NEUTRAL, BLACK, NEUTRAL};
  array_cpy(LENGTH_PATTERN, rules[0].pattern, pattern0);
  rules[0].nb_transformation = 2;
  rules[0].dx[0] = 0;
  rules[0].dy[0] = 1;
  rules[0].transformation[0] = BLACK;
  rules[0].dx[1] = 0;
  rules[0].dy[1] = 0;
  rules[0].transformation[1] = YELLOW;

  // Rule for the sand when there isn't rock on the sides and there is sand or rock underneath but the sides underneath are empty
  unsigned int pattern1[9] = {NEUTRAL, NEUTRAL, NEUTRAL,
                              NOT_GREY, YELLOW, NOT_GREY,
                              BLACK, NOT_BLACK, BLACK};
  array_cpy(LENGTH_PATTERN, rules[1].pattern, pattern1);
  rules[1].nb_transformation = 3;
  rules[1].dx[0] = -1;
  rules[1].dy[0] = 1;
  rules[1].transformation[0] = BLACK;
  rules[1].dx[1] = 1;
  rules[1].dy[1] = 1;
  rules[1].transformation[1] = BLACK;
  rules[1].dx[2] = 0;
  rules[1].dy[2] = 0;
  rules[1].transformation[2] = YELLOW;

  // Rule for the sand when the right side isn't rock and the bottom right is empty
  unsigned int pattern2[9] = {NEUTRAL, NEUTRAL, NEUTRAL,
                              NEUTRAL, YELLOW, NOT_GREY,
                              NOT_BLACK, NOT_BLACK, BLACK};
  array_cpy(LENGTH_PATTERN, rules[2].pattern, pattern2);
  rules[2].nb_transformation = 2;
  rules[2].dx[0] = 1;
  rules[2].dy[0] = 1;
  rules[2].transformation[0] = BLACK;
  rules[2].dx[1] = 0;
  rules[2].dy[1] = 0;
  rules[2].transformation[1] = YELLOW;

  // Rule for the sand when the left side isn't rock and the bottom left is empty
  unsigned int pattern3[9] = {NEUTRAL, NEUTRAL, NEUTRAL,
                              NOT_GREY, YELLOW, NEUTRAL,
                              BLACK, NOT_BLACK, NOT_BLACK};
  array_cpy(LENGTH_PATTERN, rules[3].pattern, pattern3);
  rules[3].nb_transformation = 2;
  rules[3].dx[0] = -1;
  rules[3].dy[0] = 1;
  rules[3].transformation[0] = BLACK;
  rules[3].dx[1] = 0;
  rules[3].dy[1] = 0;
  rules[3].transformation[1] = YELLOW;

  // Rule for the sand when there is rock on the left and the sides underneath are empty
  unsigned int pattern4[9] = {NEUTRAL, NEUTRAL, NEUTRAL,
                              GREY, YELLOW, NOT_GREY,
                              BLACK, NOT_BLACK, BLACK};
  array_cpy(LENGTH_PATTERN, rules[4].pattern, pattern4);
  rules[4].nb_transformation = 2;
  rules[4].dx[0] = 1;
  rules[4].dy[0] = 1;
  rules[4].transformation[0] = BLACK;
  rules[4].dx[1] = 0;
  rules[4].dy[1] = 0;
  rules[4].transformation[1] = YELLOW;

  // Rule for the sand when there is rock on the right and the sides underneath are empty
  unsigned int pattern5[9] = {NEUTRAL, NEUTRAL, NEUTRAL,
                              NOT_GREY, YELLOW, GREY,
                              BLACK, NOT_BLACK, BLACK};
  array_cpy(LENGTH_PATTERN, rules[5].pattern, pattern5);
  rules[5].nb_transformation = 2;
  rules[5].dx[0] = -1;
  rules[5].dy[0] = 1;
  rules[5].transformation[0] = BLACK;
  rules[5].dx[1] = 0;
  rules[5].dy[1] = 0;
  rules[5].transformation[1] = YELLOW;
}

void rules_init()
{
  if (ACHIEV == 0 || ACHIEV == 1)
    rules_init_gol();
  else if (ACHIEV == 2)
    rules_init_particule();
}

unsigned int rules_count()
{
  return NB_RULE;
}

struct rule *rule_get(unsigned int i)
{
  return &rules[i];
}

int surrounding_idx(int idxs[], unsigned int i, unsigned int j)
{
  int cpt = 0;
  for (int row = 0; row < 3; ++row)
  {
    for (int col = 0; col < 3; ++col)
    {
      int new_i = (i - 1 + row + HEIGHT) % HEIGHT;
      int new_j = (j - 1 + col + WIDTH) % WIDTH;
      idxs[cpt++] = coord_to_idx(new_i, new_j, WIDTH);
    }
  }
  return 0;
}

int rule_match_gol(const struct world *w, const struct rule *r, unsigned int i, unsigned int j)
{
  int idxs[9] = {};
  surrounding_idx(idxs, i, j);
  unsigned int colors[9] = {};
  for (int k = 0; k < 9; ++k)
  {
    switch ((*w).t[idxs[k]])
    {
    case WHITE:
    case RED:
    case BLUE:
    case GREEN:
      colors[k] = NEUTRAL;
      break;
    default:
      colors[k] = BLACK;
      break;
    }
  }
  return array_cmp(9, (*r).pattern, colors);
}

int rule_match_particule(const struct world *w, const struct rule *r, unsigned int i, unsigned int j)
{
  int idxs[9] = {};
  surrounding_idx(idxs, i, j);
  unsigned int colors[9] = {};

  for (int k = 0; k < 3; ++k)
  {
    colors[k] = NEUTRAL;
  }
  if ((*w).t[idxs[7]] == BLACK)
  {
    for (int k = 3; k < 9; ++k)
    {
      colors[k] = NEUTRAL;
    }
    colors[4] = (*w).t[idxs[4]];
    colors[7] = BLACK;
  }
  else
  {
    for (int k = 3; k < 6; ++k)
    {
      colors[k] = ((*w).t[idxs[k]] != GREY) ? NOT_GREY : GREY;
    }
    for (int k = 6; k < 9; ++k)
    {
      colors[k] = ((*w).t[idxs[k]] != BLACK) ? NOT_BLACK : BLACK;
      colors[k - 3] = (colors[k] == NOT_BLACK) ? NEUTRAL : colors[k - 3];
    }
    colors[4] = (*w).t[idxs[4]];
  }
  return array_cmp(9, (*r).pattern, colors);
}

int rule_match(const struct world *w, const struct rule *r, unsigned int i, unsigned int j)
{
  if (ACHIEV == 0 || ACHIEV == 1)
    return rule_match_gol(w, r, i, j);
  else if (ACHIEV == 2)
    return rule_match_particule(w, r, i, j);
}

unsigned int rule_num_changes(const struct rule *r)
{
  return (*r).nb_transformation;
}

unsigned int rule_change_to(const struct rule *r, unsigned int idx)
{
  return (*r).transformation[idx];
}

int rule_change_dx(const struct rule *r, unsigned int idx)
{
  return (*r).dx[idx];
}

int rule_change_dy(const struct rule *r, unsigned int idx)
{
  return (*r).dy[idx];
}