//
//  game.c
//  Snake
//
//  Created by Alexandre Kahn on 11/12/2016.
//  Copyright © 2016 Alexandre Kahn. All rights reserved.
//

#include "game.h"

int counter = 0;
bool game_running = true;
bool not_paused = true;

void game_loop(int width, int height){
    while (game_running) {
        read_input(width, height, game_running);
        if (not_paused){
            move_snake(width, height);
            counter++;
            SDL_Delay(100);
            printf("%i", counter);
            if (counter > 100) {
                make_apple(height, width, SPECIAL_FOOD);
                counter = 0;
            }
        }
        draw_grid(width, height);
    }
    save_to_file();
    deallocate_snake();
    deallocate_grid(width, height);
    while(1){
        read_input(width, height, game_running);
        draw_game_over(width, height);
    }
}
void pause_game(){
    if (not_paused){
        not_paused = false;
    }
    else{
        not_paused = true;
    }
}

