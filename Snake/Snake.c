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

int snake_length = 0;
 

void allocate_snake(int height, int width){
    snake.snakebody = (struct Bodypart*)malloc(snake_length * sizeof(struct Bodypart));
    snake.snakebody[0].direction = RIGHT;
    snake.snakebody[0].coordinates.x = floor(height/2);
    snake.snakebody[0].coordinates.y =  floor(width/2);
    snake.snakebody[0].is_head = 1;
    }

struct Coordinate get_coordinates(int part){
    return snake.snakebody[part].coordinates;
}
void extend_snake(int x, int y){
    snake.snakebody = realloc(snake.snakebody, (snake_length * sizeof(struct Bodypart)));
    snake.snakebody[snake_length].coordinates.x=x;
    snake.snakebody[snake_length].coordinates.y=y;
    snake.snakebody[snake_length].is_head = 0;
}
void snake_eat(int x, int y){
    snake_length++;
    extend_snake(x,y);
}

void move_head(int width, int height){
      //the head
    if (snake.snakebody[0].direction == UP){
        if (snake.snakebody[0].coordinates.y == 0){
            snake.snakebody[0].coordinates.y = height - 1;
        }
        else snake.snakebody[0].coordinates.y--;
    }
    else if (snake.snakebody[0].direction == DOWN){
        if (snake.snakebody[0].coordinates.y == height -1){
            snake.snakebody[0].coordinates.y = 0;
        }
        else snake.snakebody[0].coordinates.y++;
    }
    else if (snake.snakebody[0].direction ==  RIGHT){
        if (snake.snakebody[0].coordinates.x == width -1){
            snake.snakebody[0].coordinates.x = 0;
        }
        else snake.snakebody[0].coordinates.x++;
    }
    else if (snake.snakebody[0].direction == LEFT){
        if (snake.snakebody[0].coordinates.x == 0){
            snake.snakebody[0].coordinates.x = width -1;
        }
        else snake.snakebody[0].coordinates.x--;
    }
}
void check_apple(int width, int height){
    int x_co = snake.snakebody[0].coordinates.x;
    int y_co = snake.snakebody[0].coordinates.y;
    if (get_cell(x_co, y_co)->state == APPLE){
        snake_eat(x_co, y_co);
        eat_apple(x_co, y_co, width,height);
    }
}
//Idee voor de slang te verlengen, array achterstevoren aflopen en get_bodypart(n)->coordinates.x = get_bodypart(n-1)->coordinates.x
void move_tail(){
    if (snake_length < snake_max_size && snake_length > 0){
        for (int i = snake_length; i > 0 ; i--) {
            snake.snakebody[i].coordinates.x = snake.snakebody[i-1].coordinates.x;
            snake.snakebody[i].coordinates.y = snake.snakebody[i-1].coordinates.y;
        }
    }//else newlevel
}
void move_snake(int width, int height){
    move_tail();
    check_apple(width, height);
    move_head(width, height);
    
}

void change_direction(int direction){
    int snake_direction =snake.snakebody[0].direction;
    if (snake_direction == UP){
        if (direction == DOWN){
            printf("Not an option");
        }
        else{
            snake.snakebody[0].direction = direction;
        }
    }
    if (snake_direction == DOWN){
        if (direction == UP){
            printf("Not an option");
        }
        else{
            snake.snakebody[0].direction = direction;
        }
    }
    if (snake_direction == RIGHT){
        if (direction == LEFT){
            printf("Not an option");
        }
        else{
            snake.snakebody[0].direction = direction;
        }
    }
    if (snake_direction == LEFT){
        if (direction == RIGHT){
            printf("Not an option");
        }
        else{
            snake.snakebody[0].direction = direction;
        }
    }
}
void initialize_snake(int grid_width, int grid_height){
    allocate_snake(grid_height, grid_height);
    struct Coordinate coord = get_coordinates(0);
    int x = coord.x;
    printf("%i",x);
}

