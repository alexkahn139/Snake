//
//  input_output.h
//  Snake
//
//  Created by Alexandre Kahn on 22/12/2016.
//  Copyright © 2016 Alexandre Kahn. All rights reserved.
//

#ifndef inputoutput_h
#define inputoutput_h

#include <stdlib.h>

#include <stdio.h>
#include "grid.h"
#include "snake.h"



void open_file();
void close_file();
void save_to_file();
void update_highscore(int score);
void save_snake_state(int grid_height, int grid_width);
void load_snake_state(int grid_height, int grid_width);
void load_walls(int grid_height, int grid_width);
void load_apple(int grid_height, int grid_width);
void load_special(int grid_height, int grid_width);
void save_apples_state(int grid_height, int grid_width);
void save_special_state(int grid_height, int grid_width);
int get_highscore();
#endif /* input_output_h */
