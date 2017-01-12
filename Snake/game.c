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
int special_active_counter = 0;
bool special_active = false;


void game_loop(int width, int height){
    while (game_running) {
        int delay = 100;
        read_input(width, height, game_running);
        if (not_paused){
            move_snakes(width, height);
            delay = delay - floor(get_score()/100); // Kind of level system, every time the score gets higher the speed goes up
            counter++;
            SDL_Delay(delay);
            if (counter >500) {
                make_apple(height, width, SPECIAL_FOOD);
                counter = 0;
                special_active = true;
            }
            if (special_active) {
                special_active_counter++;
            }
            if (special_active_counter > 50) {
                for (int x = 0; x < width; x++) {
                    for (int y = 0; y < height; y++) {
                        if (get_cell(x, y)->state == SPECIAL_FOOD) {
                            get_cell(x, y)->state = NORMAL;
                        }
                    }
                }
                special_active = false;
                special_active_counter = 0;
            }
        }
        draw_grid(width, height);
    }
    save_to_file();
    deallocate_snake(1);
    deallocate_snake(2);
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
bool get_special_active(){
    return special_active;
}
void set_special(bool active){
    special_active = active;
}
