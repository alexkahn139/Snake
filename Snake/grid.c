//
//  grid.c
//  Snake
//
//  Created by Alexandre Kahn on 11/12/2016.
//  Copyright © 2016 Alexandre Kahn. All rights reserved.


//  Based on the skeleton files given for the first task.

#include "grid.h"

static struct Cell*** grid;

struct Cell *get_cell(int x, int y) {
    return grid[x][y];
}

struct Coordinate {
    int x, y;
};


struct Cell *** allocate_grid(int grid_width, int grid_height){
    struct Cell *** grid = malloc(grid_height * sizeof(struct Cell **));
    for (int y = 0;y < grid_height; y++) {
        struct Cell ** row = malloc(grid_width * sizeof(struct Cell *));
        for (int x = 0; x < grid_width; x++) {
            struct Cell * cell_in_grid = (struct Cell *)malloc(sizeof(struct Cell *));
            row[x] = cell_in_grid;
        }
        grid[y] = row;
    }
    return grid;
}

void initialize_grid(int grid_height, int grid_width){
    grid = allocate_grid(grid_width, grid_height);
}
