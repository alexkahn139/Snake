//
//  grid.h
//  Snake
//
//  Created by Alexandre Kahn on 11/12/2016.
//  Copyright © 2016 Alexandre Kahn. All rights reserved.
//

#ifndef grid_h
#define grid_h
#include <stdio.h>
#include <stdlib.h>
#include "Snake.h"
#include <math.h>

void initialize_grid(int height, int width);
extern int nr_of_walls;
// Stelt de verschillende staten die een vakje kan hebben voor
enum State {
    NORMAL,
    APPLE,
    SPECIAL_FOOD,
    WALL
};

struct Cell {
    enum State state;
};

void deallocate_grid(int grid_width, int grid_height);

/*
 * Geeft een pointer terug naar de Cell die zich bevindt op positie (x,y) in het veld.
 */
struct Cell *get_cell(int x, int y);
void eat_apple(int x, int y, int grid_height, int grid_width);
#endif /* grid_h */
