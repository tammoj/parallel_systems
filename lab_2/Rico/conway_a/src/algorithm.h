#ifndef CONWAY_ALGORITHM_H
#define CONWAY_ALGORITHM_H

#include "map.h"
#include "intermap.h"


// interface
void conway_solve(map *map, intermap *inter);

void conway_solve_border(intermap *inter, int t);
void conway_solve_core(map *map, intermap *inter, int t);


#endif // CONWAY_ALGORITHM_H
