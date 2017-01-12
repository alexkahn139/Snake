//
//  Snake.c
//  Snake
//
//  Created by Alexandre Kahn on 11/12/2016.
//  Copyright © 2016 Alexandre Kahn. All rights reserved.
//
// http://www.learn-c.org/en/Linked_lists

#include "snake.h"



struct Snake * snake1;
struct Snake * snake2;


int nr_of_snakes = 0;
int snake_length = 1;
struct Bodypart last_part;
struct Bodypart snake_head1;
struct Bodypart snake_head2;

int score = 0;
int get_score(){
    return score;
}
void set_score(int new){
    score = new;
}

void allocate_snake(int height, int width, int snake_nr){
    if (snake_nr == 1){
        snake1= malloc(sizeof(struct Snake *));
    }
    else if (snake_nr == 2){
        snake2 = malloc(sizeof(struct Snake *));
    }
    
    get_snake(snake_nr)->snakebody = malloc(sizeof(struct Bodypart *));
    get_snake(snake_nr)->snakebody->coordinates = malloc(sizeof(struct Coordinate *));
    get_snake(snake_nr)->snakebody->next = NULL;
    if (snake_nr == 1){
        snake_head1 = * get_snake(snake_nr)->snakebody;
    }
    else {
        snake_head2 = * get_snake(snake_nr)->snakebody;
    }
    nr_of_snakes++;
}

void initialize_snake(int width, int height, int snake_nr){
    get_snake(snake_nr)->direction = RIGHT;
    get_snake(snake_nr)->snakebody->coordinates->x = floor(height/2);
    get_snake(snake_nr)->snakebody->coordinates->y =  floor(width/2);
}

void deallocate_snake(snake_nr){
    if (get_nr_of_snakes() == 2){
        struct Bodypart * current = get_snake(snake_nr)->snakebody;
        while(current != NULL){
            struct Bodypart * next = current->next;
            free(current->coordinates);
            free(current);
            current = next;
        }
        free(get_snake(snake_nr));
    }
}

void extend_snake(int x, int y, int snake_nr){
    struct Bodypart * current = get_snake(snake_nr)->snakebody;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = malloc(sizeof(struct Bodypart *));
    current->next->coordinates = malloc(sizeof(struct Coordinate *));
    current->next->coordinates->x = x;
    current->next->coordinates->y = y;
    current->next->next = NULL;
}

void snake_eat(int x, int y, int snake_nr){
    snake_length++;
    extend_snake(x,y, snake_nr);
}

void move_head(int width, int height, int snake_nr){
    //the head
    struct Bodypart head;
    if (snake_nr == 1) {
        head = snake_head1;
    }
    else{
        head = snake_head2;
    }
    if (get_snake(snake_nr)->direction == UP){
        if (head.coordinates->y == 0){
            head.coordinates->y = height - 1;
        }
        else head.coordinates->y--;
    }
    else if (get_snake(snake_nr)->direction == DOWN){
        if (head.coordinates->y == height - 1){
            head.coordinates->y = 0;
        }
        else head.coordinates->y++;
    }
    else if (get_snake(snake_nr)->direction ==  RIGHT){
        if (head.coordinates->x == width - 1){
            head.coordinates->x = 0;
        }
        else head.coordinates->x++;
    }
    else if (get_snake(snake_nr)->direction == LEFT){
        if (head.coordinates->x == 0){
            head.coordinates->x = width - 1;
        }
        else head.coordinates->x--;
    }
}

void check_apple(int width, int height, int x, int y, int snake_nr){
    if (get_cell(x, y)->state == APPLE){
        snake_eat(x, y, snake_nr);
        eat_apple(x, y, width,height);
        score = score + 10;
    }
    else if (get_cell(x, y)->state == SPECIAL_FOOD){
        snake_eat(x, y, snake_nr);
        score = score + 20;
        get_cell(x, y)->state = NORMAL;
    }
}

void check_wall(){
    int x = snake_head1.coordinates->x;
    int y = snake_head1.coordinates->y;
    if (get_cell(x, y)->state ==WALL){
        game_running = false;
    }
    if (snake2 != NULL){
        x = snake_head2.coordinates->x;
        y = snake_head2.coordinates->y;
        if (get_cell(x, y)->state ==WALL){
            game_running = false;
        }
    }
}

bool check_bodyparts_loop(int x, int y, int snake_nr){
    struct Bodypart * current = get_snake(snake_nr)->snakebody->next; //Anders checkt die de head
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
    int x_co = snake_head1.coordinates->x;
    int y_co = snake_head1.coordinates->y;
    bool snake_1_no_collision = true;
    game_running = check_bodyparts_loop(x_co, y_co, 1);
    if (nr_of_snakes == 2){
        snake_1_no_collision = check_bodyparts_loop(x_co, y_co, 1) && check_bodyparts_loop(x_co, y_co, 2);
        int x_co_2 = snake_head2.coordinates->x;
        int y_co_2 = snake_head2.coordinates->y;
        bool heads_collision = x_co == x_co_2 && y_co == y_co_2;
        game_running =  !heads_collision &&
        check_bodyparts_loop(x_co_2, y_co_2, 1) &&
        check_bodyparts_loop(x_co_2, y_co_2, 2) &&
        snake_1_no_collision;
    }
}

void move_tail(int snake_nr){
    int last_x =get_snake(snake_nr)->snakebody->coordinates->x;
    int last_y= get_snake(snake_nr)->snakebody->coordinates->y;
    struct Bodypart * current = get_snake(snake_nr)->snakebody;
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


void move_snake(int width, int height, int snake_nr){
    struct Bodypart snake_head;
    if (snake_nr == 1) {
        snake_head = snake_head1;
    }
    else {
        snake_head = snake_head2;
    }
    int old_x =snake_head.coordinates->x;
    int old_y =snake_head.coordinates->y;
    move_tail(snake_nr);
    move_head(width, height, snake_nr);
    
    check_apple(width, height, old_x, old_y, snake_nr);
    check_bodyparts_collision();
    check_wall();
    update_highscore(score);
}
void move_snakes(int width, int height){
    move_snake(width, height, 1);
    if (nr_of_snakes > 1) {
        move_snake(width, height, 2);
    }
}
void change_direction(int direction, int snake_nr){ // Could be done with modulo, but this is way easier to read
    int snake_direction = get_snake(snake_nr)->direction;
    if (snake_direction == UP){
        if (direction == DOWN){
            printf("Not an option");
        }
        else{
            get_snake(snake_nr)->direction = direction;
        }
    }
    if (snake_direction == DOWN){
        if (direction == UP){
            printf("Not an option");
        }
        else{
            get_snake(snake_nr)->direction = direction;
        }
    }
    if (snake_direction == RIGHT){
        if (direction == LEFT){
            printf("Not an option");
        }
        else{
            get_snake(snake_nr)->direction = direction;
        }
    }
    if (snake_direction == LEFT){
        if (direction == RIGHT){
            printf("Not an option");
        }
        else{
            get_snake(snake_nr)->direction = direction;
        }
    }
}
struct Snake * get_snake(int nr){
    if (nr == 1){
        return snake1;
    }
    else if (nr == 2){
        return snake2;
    }
    else return 0;
}

int get_nr_of_snakes(){
    return nr_of_snakes;
}
