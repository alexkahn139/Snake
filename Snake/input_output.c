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
    /*
    fprintf(fp, "%i", grid_height);
    fputs("  ", (FILE*)fp);
    fprintf(fp, "%i", grid_width);
    fputs("  ", (FILE*)fp);
    
    fprintf(fp, "%i", nr_of_walls);
    for (int y = 0; y < grid_height; y++) {      // De coordinaten van de muren opslaan
        for (int x = 0; x < grid_width; x++){
            if (get_cell(x, y)->state == WALL){
                fputs(" ", (FILE*)fp);
                fprintf(fp, "%i", x);
                fputs(" ", (FILE*)fp);
                fprintf(fp, "%i", y);
            }
        }
    }*/
    // De coordinaten van de slang opslaan
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
    fputs(" ", (FILE*)fp);
    for (int y = 0; y< grid_height; y++) {      // De coordinaten van de appel(s) opslaan
        for (int x = 0; x < grid_width; x++){
            if (get_cell(x, y)->state == APPLE){
                fprintf(fp, "%i", x);
                fputs(" ", (FILE*)fp);
                fprintf(fp, "%i", y);
            }
        }
    }
    close_file();
}
void load_game_state(int grid_height, int grid_width){

        /*
        struct Snake snake = get_snake();
        fscanf(fp, "%s",buff);
        snake_length = atoi(buff);
        fscanf(fp,"%s",buff);
        int direction=atoi(buff);
        for (int i = 0; i < snake_length; i++) {
            fscanf(fp, "%s", buff);
            snake.snakebody[i].coordinates.x = atoi(buff);
            fscanf(fp, "%s", buff);
            snake.snakebody[i].coordinates.y = atoi(buff);
            snake.snakebody[i].direction = direction;
        }
        fscanf(fp, "%s", buff);
        int x = atoi(buff);
        int y = atoi(buff);
        get_cell(x, y)->state=APPLE;
        fclose(fp);
        remove("game_state.txt");
               */

     
}
void load_walls(int grid_height, int grid_width){
    if (fp == fopen ("walls.txt","r")){
        fp=fopen("walls.txt", "r+");   //Als de file bestaat gewoon inlezen
        fscanf(fp, "%s", buff);             // Leest de grootte van het veld in
        grid_height = atoi(buff);
        fscanf(fp, "%s", buff);
        grid_width = atoi(buff);
        fscanf(fp, "%s", buff);
        nr_of_walls = atoi(buff);            // Plaatst de muren op de correcte plek
        for (int i = 0; i < nr_of_walls; i++){
            fscanf(fp, "%s", buff);
            int x = atoi(buff);
            fscanf(fp, "%s", buff);
            int y = atoi(buff);
            get_cell(x,y)->state=WALL;
        }
    }
}
