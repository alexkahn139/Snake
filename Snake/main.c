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
#include "Snake.h"
#include "game.h"


int main(int argc, char *argv[]) {
    srand((unsigned int)time(NULL));
    

    if (argc == 3){ //3 argumenten + ./main
        int height = atoi(argv[1]);
        int width = atoi(argv[2]);
        
        initialize_grid(height, width);
        initialize_gui(height, width);
        initialize_snake(width, height);
        
        game_loop(width, height);
        
        //while (1) { read_input(width, height); }
    }
    else {
        printf("You need to give 2 arguments \n");
    }
    return 0;
}
