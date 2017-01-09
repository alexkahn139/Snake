//
//  input_output.c
//  Snake
//
//  Created by Alexandre Kahn on 22/12/2016.
//  Copyright © 2016 Alexandre Kahn. All rights reserved.
//

#include "inputoutput.h"


FILE *fp;
char buff[255];
int played_games = 0;

int highscore = 0;
int get_highscore(){
    return highscore;
}
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
void save_snake_state(int grid_height, int grid_width){
    fp=fopen("snake.txt", "w+");
    fprintf(fp, "%i",snake_length);
    struct Snake *snake = get_snake();
    fputs(" ", (FILE*)fp);
    fprintf(fp, "%i", snake->direction);
    struct Bodypart * current = snake->snakebody;
    while (current != NULL) {
        fputs(" ", (FILE*)fp);
        fprintf( fp,"%i",current->coordinates->x);
        fputs(" ", (FILE*)fp);
        fprintf( fp,"%i",current->coordinates->y);
        current = current->next;
    }
    fputs(" ", fp);
    fprintf(fp, "%i", get_score()); //Hier omdat de score enkel moet bijgehouden worden als de slang ook opgeslagen wordt
}


void save_apples_state(int grid_height, int grid_width){
    fp=fopen("apples.txt", "w+");
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

void save_special_state(int grid_height, int grid_width){
    fp=fopen("specials.txt", "w+");
    for (int y = 0; y< grid_height; y++) {      // De coordinaten van de special opslaan
        for (int x = 0; x < grid_width; x++){
            if (get_cell(x, y)->state == SPECIAL_FOOD){
                fprintf(fp, "%i", x);
                fputs(" ", (FILE*)fp);
                fprintf(fp, "%i", y);
            }
        }
    }
    close_file();
}

void load_snake_state(int grid_height, int grid_width){
    allocate_snake(grid_height, grid_width);
    if (fp == fopen ("snake.txt","r")){
        fp=fopen("snake.txt", "r+");
        struct Snake *snake = get_snake();
        fscanf(fp, "%s",buff);
        snake_length = atoi(buff);
        fscanf(fp,"%s",buff);
        int direction=atoi(buff);
        snake->direction = direction;
        fscanf(fp, "%s", buff);
        snake->snakebody->coordinates->x = atoi(buff); //Eerste moeten de coordinaten van verandert worden, rest moet gealloceerd worden
        fscanf(fp, "%s", buff);
        snake->snakebody->coordinates->y = atoi(buff);
        for (int i = 1; i < snake_length; i++) {
            //struct Bodypart * current = snake->snakebody;
            fscanf(fp, "%s", buff);
            int x = atoi(buff);
            fscanf(fp, "%s", buff);
            int y = atoi(buff);
            extend_snake(x, y);
        }
        fscanf(fp, "%s", buff);
        set_score(atoi(buff));
        fclose(fp);
        remove("snake.txt");
    }
    else{
        initialize_snake(grid_height, grid_width);
    }
}
void load_apple(int grid_height, int grid_width){
    if (fp == fopen ("apples.txt","r")){
        fp=fopen("apples.txt", "r+");
        fscanf(fp, "%s", buff);
        int x = atoi(buff);
        fscanf(fp, "%s",buff);
        int y = atoi(buff);
        get_cell(x, y)->state=APPLE;
        fclose(fp);
        remove("apples.txt");
    }
    else{
        make_apple(grid_height, grid_width, APPLE);
    }
}
void load_special(int grid_height, int grid_width){
    if (fp == fopen ("specials.txt","r")){
        fp=fopen("specials.txt", "r+");
        fscanf(fp, "%s", buff);
        int x = atoi(buff);
        fscanf(fp, "%s",buff);
        int y = atoi(buff);
        get_cell(x, y)->state=SPECIAL_FOOD;
        fclose(fp);
        remove("specials.txt");
        bool special = get_special_active();
        special = true;
        
    }
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
    close_file();
}
