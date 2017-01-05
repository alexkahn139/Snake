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
#include <stdbool.h>


struct Snake * snake;

int snake_length = 1;

struct Bodypart last_part;
struct Bodypart snake_head;

int score = 0;
int get_score(){
    return score;
}

void allocate_snake(int height, int width){
    snake = (struct Snake*)malloc(sizeof(struct Snake *));
    snake->snakebody = (struct Bodypart*) malloc(sizeof(struct Bodypart *));
    snake->snakebody->coordinates = (struct Coordinate *)malloc(sizeof(struct Coordinate *));
    snake->snakebody->next = NULL;
    last_part = * snake->snakebody;
    snake_head = * snake->snakebody;
}
void init_snake(int height, int width){
    snake->direction = RIGHT;
    snake->snakebody->coordinates->x = floor(height/2);
    snake->snakebody->coordinates->y =  floor(width/2);
    
}
void deallocate_snake(){
    struct Bodypart * current = snake->snakebody;
    while(current != NULL){
        struct Bodypart * next = current->next;
        free(current->coordinates);
        free(current);
        current = next;
    }
    free(snake);
}


void extend_snake(int x, int y){
    struct Bodypart * current = snake->snakebody;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = (struct Bodypart *)malloc(sizeof(struct Bodypart *));
    current->next->coordinates = (struct Coordinate *) malloc(sizeof(struct Coordinate *));
    current->next->coordinates->x = x;
    current->next->coordinates->y = y;
    current->next->next = NULL;
}
void snake_eat(int x, int y){
    snake_length++;
    extend_snake(x,y);
    printf("Snake is %i parts long \n",snake_length);
}

void move_head(int width, int height){
    //the head
    if (snake->direction == UP){
        if (snake_head.coordinates->y == 0){
            snake_head.coordinates->y = height - 1;
        }
        else snake_head.coordinates->y--;
    }
    else if (snake->direction == DOWN){
        if (snake_head.coordinates->y == height -1){
            snake_head.coordinates->y = 0;
        }
        else snake_head.coordinates->y++;
    }
    else if (snake->direction ==  RIGHT){
        if (snake_head.coordinates->x == width - 1){
            snake_head.coordinates->x = 0;
        }
        else snake_head.coordinates->x++;
    }
    else if (snake->direction == LEFT){
        if (snake_head.coordinates->x == 0){
            snake_head.coordinates->x = width - 1;
        }
        else snake_head.coordinates->x--;
    }
}
void check_apple(int width, int height, int x, int y){
    
    if (get_cell(x, y)->state == APPLE){
        snake_eat(x, y);
        eat_apple(x, y, width,height);
        score = score + 10;
    }
}
void check_wall(){
    int x = snake_head.coordinates->x;
    int y = snake_head.coordinates->y;
    if (get_cell(x, y)->state ==WALL){
        game_running = false;
    }
}

bool check_bodyparts_loop(int x, int y, int i){
    struct Bodypart * current = snake->snakebody->next; //Anders checkt die de head
    bool no_collision = true;
    while (current != NULL) {
        if (x == current->coordinates->x && y == current->coordinates->y){
            no_collision = false;
            break;
        }
        current = current->next;
    }
    return no_collision;
}

void check_bodyparts_collision(){
    int x_co = snake_head.coordinates->x;
    int y_co = snake_head.coordinates->y;
    game_running = check_bodyparts_loop(x_co, y_co, 2);    //Start at 1 because the head can't collide with itself
}
//Idee voor de slang te verlengen, array achterstevoren aflopen en get_bodypart(n)->coordinates.x = get_bodypart(n-1)->coordinates.x
void move_tail(){
    int last_x =snake->snakebody->coordinates->x;
    int last_y= snake->snakebody->coordinates->y;
    struct Bodypart * current = snake->snakebody;
    while (current != NULL) {
        int x = current->coordinates->x;
        int y = current->coordinates->y;
        current->coordinates->x = last_x;
        current->coordinates->y = last_y;
        current = current->next;
        last_x=x;
        last_y=y;
    }
    
}
void move_snake(int width, int height){
    
    int old_x =snake_head.coordinates->x;
    int old_y =snake_head.coordinates->y;
    move_tail();
    move_head(width, height);
    
    check_apple(width, height, old_x, old_y);
    check_bodyparts_collision();
    check_wall();
    update_highscore(score);
}


void change_direction(int direction){ // Could be done with modulo, but this is way easier to read
    int snake_direction = snake->direction;
    if (snake_direction == UP){
        if (direction == DOWN){
            printf("Not an option");
        }
        else{
            snake->direction = direction;
        }
    }
    if (snake_direction == DOWN){
        if (direction == UP){
            printf("Not an option");
        }
        else{
            snake->direction = direction;
        }
    }
    if (snake_direction == RIGHT){
        if (direction == LEFT){
            printf("Not an option");
        }
        else{
            snake->direction = direction;
        }
    }
    if (snake_direction == LEFT){
        if (direction == RIGHT){
            printf("Not an option");
        }
        else{
            snake->direction = direction;
        }
    }
}
void initialize_snake(int grid_width, int grid_height){
    allocate_snake(grid_height, grid_height);
    init_snake(grid_height, grid_height);
    
}
struct Snake * get_snake(){
    return snake;
}
