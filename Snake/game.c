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

void game_loop(int width, int height){
    while (game_running) {
        read_input(width, height);
        move_snake(width, height);
        draw_grid(width, height);
        SDL_Delay(100);
    }
    save_to_file();
}


