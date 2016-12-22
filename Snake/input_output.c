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
