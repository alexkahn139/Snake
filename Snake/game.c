//
//  game.c
//  Snake
//
//  Created by Alexandre Kahn on 11/12/2016.
//  Copyright © 2016 Alexandre Kahn. All rights reserved.
//

#include "game.h"
#include<unistd.h>



void game_loop(int width, int height){
    while (1) {
        
        read_input(width, height);
        //sleep(1);
        move_snake(width, height);
        draw_grid(width, height);
        //sleep(1);
    }
}


