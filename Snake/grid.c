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
int nr_of_walls = 0;
struct Cell *get_cell(int x, int y) {
    return grid[x][y];
}


struct Cell *** allocate_grid(int grid_width, int grid_height){
    struct Cell *** grid = malloc(grid_height * sizeof(struct Cell **));
    for (int y = 0 ;y < grid_height; y++) {
        struct Cell ** row = malloc(grid_width * sizeof(struct Cell *));
        for (int x = 0; x < grid_width; x++) {
            struct Cell * cell_in_grid = malloc(sizeof(struct Cell *));
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

static struct Coordinate* generate_random_apple(int grid_width, int grid_height) {
    int x = rand() %grid_width;
    int y = rand() %grid_height;
    
    struct Coordinate *coordinates_of_apple = malloc(1 * sizeof(struct Coordinate));
    struct Coordinate coordinate = {x, y};
    coordinates_of_apple[1] = coordinate;
    return coordinates_of_apple;
}
static struct Coordinate* generate_walls(int grid_width, int grid_height){
    nr_of_walls = (floor(grid_width/5)*4 + floor(grid_width/5)*4 - 2);
    struct Coordinate *coordinates_of_walls = malloc(nr_of_walls * sizeof(struct Coordinate));
    int i = 0;
    while(i < nr_of_walls + 1) {
            for (int y = 0; y < grid_height; y++){
                for (int x = 0; x < grid_width; x++){
                if (((x < 5 || x > 14) && ( y == 0 || y == grid_height-1)) || (((y < 5 || y > 14))&&( x == 0 || x == grid_width-1))){
                    i++;
                    struct Coordinate coordinate = {x, y};
                    coordinates_of_walls[i] = coordinate;
                }
            }
        }
    }
    return coordinates_of_walls;
}
void place_apple(struct Coordinate apple_coordinates[], int grid_width, int grid_height, enum State state){
    if (get_cell(apple_coordinates[1].x, apple_coordinates[1].y)->state == WALL){
        struct Coordinate *apple_coordinates = generate_random_apple(grid_width-1, grid_height-1);
        place_apple(apple_coordinates, grid_width, grid_height, state);
        free(apple_coordinates);
    }
    else{
        get_cell(apple_coordinates[1].x, apple_coordinates[1].y)->state = state;
        
    }
}
void place_walls(struct Coordinate wall_coordinates[], int nr_of_walls){
    printf("nr_of_walls = %i \n", nr_of_walls);
    for (int i = 0; i < nr_of_walls ; i++) {
        get_cell(wall_coordinates[i].x, wall_coordinates[i].y)->state = WALL;
    }
}

void make_walls(int grid_height, int grid_width){
    struct Coordinate *wall_coordinates = generate_walls(grid_height, grid_height);
    place_walls(wall_coordinates, nr_of_walls);
    free(wall_coordinates);
}
void make_apple(int grid_height, int grid_width, enum State state){
    struct Coordinate *apple_coordinates = generate_random_apple(grid_width-1, grid_height-1);
    place_apple(apple_coordinates, grid_width, grid_height, state);
    free(apple_coordinates);
}
void initialize_grid(int grid_height, int grid_width){
    grid = allocate_grid(grid_width, grid_height);
    //make_walls(grid_height, grid_width);
    //make_apple(grid_height, grid_width);
    
    
}

void eat_apple(int x, int y, int grid_height, int grid_width){
    if (get_cell(x, y)->state == APPLE){
        make_apple(grid_height, grid_width, APPLE);
    }
    get_cell(x, y)->state = NORMAL;
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
