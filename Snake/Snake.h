//
//  Snake.h
//  Snake
//
//  Created by Alexandre Kahn on 11/12/2016.
//  Copyright © 2016 Alexandre Kahn. All rights reserved.
//

#ifndef Snake_h
#define Snake_h

#include <stdio.h>
//int snake_length;

enum Direction{
    UP,
    DOWN,
    RIGHT,
    LEFT
};
struct Coordinate{
    int x;
    int y;
};
struct Snake{
    struct Bodypart* snakebody;
};
struct Bodypart{
    int is_head;
    struct Coordinate coordinates;
    enum Direction direction;
};

void initialize_snake(int grid_width, int grid_height);
void move_snake();

//extern struct Snake snake;

extern int snake_length;

int get_bodypart_coordinate_x(int part);
int get_bodypart_coordinate_y(int part);
#endif /* Snake_h */
