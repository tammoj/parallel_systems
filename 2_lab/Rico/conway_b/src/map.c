#include "map.h"

#include <stdlib.h>
#include <string.h>

// TODO delete me
#include <stdio.h>


void map_init(map *map, int duration, int width, int height) {
	map->duration = duration;
	map->width    = width;
	map->height   = height;
	map->levels = calloc(duration, sizeof(cell_list));
	
	// init lists
	for (int i = 0; i < duration; ++i)
		cell_list_init(&map->levels[i]);
}

void map_free(map *map) {
	for (int t = 0; t < map->duration; ++t)
		cell_list_free(&map->levels[t]);
	
	free(map->levels);
}

cell_list *map_get_level(map *map, int t) {
	return &map->levels[t];
}

int map_count(map *map, int t) {
	int sum = 0;
	
	int x, y;
	map_restart(map, t);
	while (map_next(map, t, &x, &y))
		++sum;
	
	return sum;
}

void map_append(map *map, int t, int x, int y) {
	cell_list *level = map_get_level(map, t);
	
	cell_list_append(level, x, y);
}

bool map_next(map *map, int t, int *x, int *y) {
	cell_list *level = map_get_level(map, t);
	
	return cell_list_next(level, x, y);
}

void map_restart(map *map, int t) {
	cell_list *level = map_get_level(map, t);
	
	cell_list_restart(level);
}

void map_print(map *map, int t, int x0, int y0, int x1, int y1) {
	int width  = x1 - x0 + 1;
	int height = y1 - y0 + 1;
	
	bool arr[width][height];
	memset(arr, 0, width*height);
	
	int x, y;
	
	// collect living cells
	map_restart(map, t);
	while (map_next(map, t, &x, &y)) {
		if (x >= x0 && x <= x1 &&
			y >= y0 && y <= y1   )
		{
			arr[x-x0][y-y0] = true;
		}
	}
	
	// print cells
	printf("t=%d x=%d-%d y=%d-%d:\n", t, x0, x1, y0, y1);

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if (arr[x][y])
				printf("X");
			else
				printf(" ");
		}
		
		printf("\n");
	}
}

