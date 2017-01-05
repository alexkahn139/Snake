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
void allocate_snake(int height, int width);
void initialize_snake(int width, int height);
void move_snake(int width, int height);
void extend_snake(int x, int y);
//extern struct Snake snake;

extern int snake_length;

struct Coordinate get_coordinates(int part);

void change_direction(int direction);

struct Snake * get_snake();

int get_score();

void deallocate_snake();

#endif /* Snake_h */
