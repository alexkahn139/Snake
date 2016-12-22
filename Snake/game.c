//
//  game.c
//  Snake
//
//  Created by Alexandre Kahn on 11/12/2016.
//  Copyright © 2016 Alexandre Kahn. All rights reserved.
//

#include "game.h"
#include<unistd.h>
int counter = 0;
bool game_running = true;
bool not_paused = true;

void game_loop(int width, int height){
    while (game_running) {
        read_input(width, height);
        if (not_paused){
            move_snake(width, height);
            SDL_Delay(100);
        }
        draw_grid(width, height);
    }
    save_to_file();
}
void pause_game(){
    if (not_paused){
        not_paused = false;
    }
    else{
        not_paused = true;
    }
}

