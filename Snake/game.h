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
#include "Snake.h"
#include "gui.h"
#include <stdbool.h>

void game_loop(int width, int height);
extern bool game_running;

#endif /* game_h */
