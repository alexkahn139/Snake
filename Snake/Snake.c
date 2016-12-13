//
//  Snake.c
//  Snake
//
//  Created by Alexandre Kahn on 11/12/2016.
//  Copyright © 2016 Alexandre Kahn. All rights reserved.
//
// http://www.learn-c.org/en/Linked_lists

#include "Snake.h"
#include <stdlib.h>
#include <math.h>


struct Snake snake;

int snake_max_size = 25; //Na een bepaalde lengte wordt er een nieuw level begonnen

int snake_length = 1;
 

void allocate_snake(int height, int width){
    snake.snakebody = (struct Bodypart*)malloc(snake_length * sizeof(struct Bodypart));
    snake.snakebody[0].direction = RIGHT;
    snake.snakebody[0].coordinates.x = floor(height/2);
    snake.snakebody[0].coordinates.y =  floor(width/2);
    snake.snakebody[0].is_head = 1;
    }


void snake_eat(){
    snake_length++;
}

void move_head(){
      //the head
    if (snake.snakebody[0].direction == UP){
        snake.snakebody[0].coordinates.y--;
    }
    else if (snake.snakebody[0].direction == DOWN){
        snake.snakebody[0].coordinates.y++;
    }
    else if (snake.snakebody[0].direction ==  RIGHT){
        snake.snakebody[0].coordinates.x++;
    }
    else if (snake.snakebody[0].direction == LEFT){
        snake.snakebody[0].coordinates.x--;
    }
}
//Idee voor de slang te verlengen, array achterstevoren aflopen en get_bodypart(n)->coordinates.x = get_bodypart(n-1)->coordinates.x
void move_tail(){
    if (snake_length < snake_max_size && snake_length > 0){
        for (int i = snake_length; i > 0 ; i--) {
            snake.snakebody[i].coordinates.x = snake.snakebody[-1].coordinates.x;
            snake.snakebody[i].coordinates.y = snake.snakebody[i-1].coordinates.y;
        }
    }//else newlevel
}
void move_snake(){
    move_tail();
    move_head();
}
void initialize_snake(int grid_width, int grid_height){
    allocate_snake(grid_height, grid_height);
}
