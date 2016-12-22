//
//  input_output.h
//  Snake
//
//  Created by Alexandre Kahn on 22/12/2016.
//  Copyright © 2016 Alexandre Kahn. All rights reserved.
//

#ifndef input_output_h
#define input_output_h

#include <stdio.h>
#include "grid.h"



void open_file();
void close_file();
void save_to_file();
void update_highscore(int score);
void save_game_state(int grid_height, int grid_width);
void load_game_state(int grid_height, int grid_width);
void load_walls(int grid_height, int grid_width);
#endif /* input_output_h */
