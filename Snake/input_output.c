//
//  input_output.c
//  Snake
//
//  Created by Alexandre Kahn on 22/12/2016.
//  Copyright © 2016 Alexandre Kahn. All rights reserved.
//

#include "input_output.h"
#include <stdio.h>
#include <stdlib.h>

FILE *fp;
char buff[255];
int played_games = 0;

int highscore = 0;
void open_file(){
    if ((fp = fopen ("games.txt","r"))){
        fp=fopen("games.txt", "r+"); //Als de file bestaat gewoon inlezen
        fscanf(fp, "%s", buff);
        played_games = atoi(buff);
        fgets(buff, 255, (FILE*)fp);
        highscore =atoi(buff);
        printf("%i ", played_games);
        printf("%i", highscore);
        fclose(fp);
    }
    else{                       //Als de file niet bestaat
        fp = fopen ("games.txt", "wb");
        fprintf(fp, "0 0");
        fclose(fp);
    }
}

void close_file(){
    fclose(fp);
}
void save_to_file(){
    fp=fopen("games.txt", "w+");
    played_games++;
    fprintf(fp, "%i", played_games);
    fputs(" ", fp);
    fprintf(fp, "%i", highscore);
    close_file();
}
void update_highscore(int score){
    if (score > highscore) {
        highscore = score;
    }
}
void save_game_state(int grid_height, int grid_width){
    fp=fopen("game_state.txt", "w+");
    fprintf(fp, "%i", grid_height);
    fputs(" ", (FILE*)fp);
    fprintf(fp, "%i", grid_width);
    fputs(" ", (FILE*)fp);
    fprintf(fp, "%i", nr_of_walls);
    for (int y = 0; y< grid_height; y++) {      // De coordinaten van de muren opslaan
        for (int x = 0; x < grid_width; x++){
            if (get_cell(x, y)->state == WALL){
                fputs(" ", (FILE*)fp);
                fprintf(fp, "%i", x);
                fputs(" ", (FILE*)fp);
                fprintf(fp, "%i", y);
            }
        }
    }
    fputs(" ", (FILE*)fp);                      // De coordinaten van de slang opslaan
    fprintf(fp, "%i",snake_length);
    struct Snake snake = get_snake();
    fputs(" ", (FILE*)fp);
    fprintf(fp, "%i", snake.snakebody[0].direction);
    for (int i = 0; i < snake_length; i++){
        fputs(" ", (FILE*)fp);
        fprintf( fp,"%i",snake.snakebody[i].coordinates.x);
        fputs(" ", (FILE*)fp);
        fprintf( fp,"%i",snake.snakebody[i].coordinates.y);
    }
    for (int y = 0; y< grid_height; y++) {      // De coordinaten van de appel(s) opslaan
        for (int x = 0; x < grid_width; x++){
            if (get_cell(x, y)->state == APPLE){
                fputs(" ", (FILE*)fp);
                fprintf(fp, "%i", x);
                fputs(" ", (FILE*)fp);
                fprintf(fp, "%i", y);
            }
        }
    }
    close_file();
}
