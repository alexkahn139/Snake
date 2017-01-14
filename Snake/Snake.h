//
//  Snake.h
//  Snake
//
//  Created by Alexandre Kahn on 11/12/2016.
//  Copyright © 2016 Alexandre Kahn. All rights reserved.
//

#ifndef snake_h
#define snake_h
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "grid.h"
#include "game.h"


enum Direction{
    UP,
    RIGHT,
    DOWN,
    LEFT
};
struct Coordinate{
    int x;
    int y;
};
struct Snake{
    struct Bodypart * snakebody;
    enum Direction direction;
};
struct Bodypart{
    struct Coordinate * coordinates;
    struct Bodypart * next;
};
void allocate_snake(int height, int width, int snake_nr);
void initialize_snake(int width, int height, int snake_nr);
void move_snakes(int width, int height);
void extend_snake(int x, int y, int snake_nr);

extern int snake_length;

struct Coordinate get_coordinates(int part);

void change_direction(int direction, int snake_nr);

struct Snake * get_snake(int nr);

int get_score();
void set_score(int new);
void deallocate_snake(int snake_nr);

int get_nr_of_snakes();

#endif /* Snake_h */
