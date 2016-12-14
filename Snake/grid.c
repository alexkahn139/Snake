//
//  grid.c
//  Snake
//
//  Created by Alexandre Kahn on 11/12/2016.
//  Copyright © 2016 Alexandre Kahn. All rights reserved.


//  Based on the skeleton files given for the first task.

#include "grid.h"

static struct Cell*** grid;

int loops = 0;

struct Cell *get_cell(int x, int y) {
    return grid[x][y];
}
/*
struct Coordinate {
    int x, y;
};*/

void place_apple(struct Coordinate apple_coordinates[]){
    get_cell(apple_coordinates[1].x, apple_coordinates[1].y)->state = APPLE;
}

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
/*
 * Maakt een 1-dimensionale sequentiële array aan van lengte grid_width * grid_height, die opgevuld wordt door de getallen
 * gaande van 0 tot lengte - 1.
 */
//http://stackoverflow.com/questions/196017/unique-non-repeating-random-numbers-in-o1

/*
 * Genereert nr_of_mines aantal random, verschillende posities voor de mijnen die initieel in het veld geplaatst worden.
 */
static struct Coordinate* generate_random_apple(int grid_width, int grid_height) {
    int x = rand() %grid_width;
    int y = rand() %grid_height;
    
    struct Coordinate *coordinates_of_apple = malloc(1 * sizeof(struct Coordinate));
    struct Coordinate coordinate = {x, y};
    coordinates_of_apple[1] = coordinate;
    return coordinates_of_apple;
}
void make_apple(int grid_height, int grid_width){
    struct Coordinate *apple_coordinates = generate_random_apple(grid_width, grid_height);
    place_apple(apple_coordinates);
    free(apple_coordinates);
}
void initialize_grid(int grid_height, int grid_width){
    grid = allocate_grid(grid_width, grid_height);
    make_apple(grid_height, grid_width);
    
}
void eat_apple(int x, int y, int grid_height, int grid_width){
    get_cell(x, y)->state = NORMAL;
    make_apple(grid_height, grid_width);
}

void deallocate_grid(int grid_width, int grid_height){
    for (int x = 0; x < grid_width; x++) {
        for (int y = 0;y < grid_height; y++) {
            free(grid[x][y]);   //Afzonderlijke cellen dealloceren
        }
        free(grid[x]);          //De rijen dealloceren
    }
    free(grid);                 //De volledige grid dealloceren
}