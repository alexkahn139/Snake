//
//  game.h
//  Snake
//
//  Created by Alexandre Kahn on 11/12/2016.
//  Copyright © 2016 Alexandre Kahn. All rights reserved.
//

#ifndef game_h
#define game_h

#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <stdbool.h>
#include "snake.h"
#include "gui.h"
#include "inputoutput.h"

 

void game_loop(int width, int height);
extern bool game_running;
void pause_game();
bool get_special_active();




#endif /* game_h */
