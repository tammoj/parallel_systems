#include "intermap.h"

#include <stdlib.h>
#include <string.h>


void intermap_init(intermap *inter, int size) {
	cell_list_init(&inter->touched_oborder);
	cell_list_init(&inter->touched_iborder);
	cell_list_init(&inter->touched_core);
	cell_list_init(&inter->current_iborder);
	cell_list_init(&inter->current_core);
	cell_list_init(&inter->future_iborder);
	cell_list_init(&inter->future_core);
	
	inter->neighbors = calloc(size, sizeof(*inter->neighbors));
}

void intermap_free(intermap *inter) {
	cell_list_init(&inter->touched_oborder);
	cell_list_free(&inter->touched_iborder);
	cell_list_free(&inter->touched_core);
	cell_list_free(&inter->current_iborder);
	cell_list_free(&inter->current_core);
	cell_list_free(&inter->future_iborder);
	cell_list_free(&inter->future_core);
	
	free(inter->neighbors);
}

void intermap_reset_neighbors(intermap *inter, int size) {
	memset(inter->neighbors, 0, size*sizeof(*inter->neighbors));
}

void intermap_append(intermap *inter, int width, int height, int x, int y) {
	if ((x == 1 || x == width -2) ||
		(y == 1 || y == height-2))
	{
		cell_list_append(&inter->current_iborder, x, y);
	} else {
		cell_list_append(&inter->current_core, x, y);
	}
}

void intermap_commit(intermap *inter, cell_list *target) {
	// move changes to target
	cell_list_merge(target, &inter->current_iborder);
	cell_list_merge(target, &inter->current_core);
	
	// future becomes intermediate state
	cell_list_merge(&inter->current_iborder, &inter->future_iborder);
	cell_list_merge(&inter->current_core   , &inter->future_core);
}

