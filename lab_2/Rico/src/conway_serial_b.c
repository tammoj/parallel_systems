
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "map.h"
#include "conway_algorithm.h"

int main(int argc, char **argv) {
	int width = 50;
	int height = 50;
	int duration = 20;
	
	map map;
	
	map_init(&map, duration, width, height);
	
	for (int x = 14; x <= 34; ++x) {
		for (int y = 14; y <= 34; ++y) {
			map_append(&map, 0, x, y);
		}
	}
	
	conway_solve(&map);
	
	map_free(&map);
	
	return EXIT_SUCCESS;
}

