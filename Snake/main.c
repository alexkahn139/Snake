//
//  main.c
//  Snake
//
//  Created by Alexandre Kahn on 11/12/2016.
//  Copyright © 2016 Alexandre Kahn. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"
#include "gui.h"
#include "snake.h"
#include "game.h"
#include "inputoutput.h"

extern int width;
extern int height;

int main(int argc, char *argv[]) {
    srand((unsigned int)time(NULL));
    if (argc == 3){ //3 argumenten + ./main
        int height = atoi(argv[1]);
        int width = atoi(argv[2]);
        open_file();
        
        initialize_grid(height, width);
        
        load_snake_state(height, width);
        load_walls(height, width);
        load_apple(height, width);
        load_special(height, width);
        
        initialize_gui(height, width);
        game_loop(width, height);
        
    }
    else {
        printf("You need to give 2 arguments \n");
    }
    return 0;
}
