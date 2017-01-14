//
//  gui.c
//  Snake
//
//  Created by Alexandre Kahn on 12/12/2016.
//  Copyright © 2016 Alexandre Kahn. All rights reserved.
//

/*
 * Dit is het venster dat getoond zal worden en waarin het speelveld weergegeven wordt.
 * Dit venster wordt aangemaakt bij het initialiseren van de GUI en wordt weer afgebroken
 * wanneer het spel eindigt.
 */
#include "gui.h"


static SDL_Surface *window;
SDL_Surface* textSurface = NULL;
TTF_Font* font = NULL;

SDL_Color textColor = { 255, 255, 255 };


void drawText(SDL_Surface* screen, char* string, int size, int x, int y)
{
    font = TTF_OpenFont("Images/arial.ttf", size);
    
    SDL_Color foregroundColor = { 0, 0, 0 };
    //SDL_Color backgroundColor = { 255, 255, 255 };
    
    textSurface = TTF_RenderText_Solid(font, string, foregroundColor);
    
    SDL_Rect textLocation = { x, y, 0, 0 };
    
    SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
    
    SDL_FreeSurface(textSurface);
    
    TTF_CloseFont(font);
}



void stop_gui() {
    SDL_Quit();
}

SDL_Surface* images[5];

void draw_cell(int x, int y, int kleur){
    SDL_Rect offset;
    offset.x = x*IMAGE_WIDTH;
    offset.y = y*IMAGE_HEIGHT;
    
    SDL_BlitSurface(images[kleur], NULL, window, &offset);
    
}
void draw_snake_part(){
    SDL_Rect offset;
    struct Snake * snake = get_snake(1);
    struct Bodypart * current = snake->snakebody;
    if (current!= NULL) {
        while (current->next != NULL) {
            int x = current->coordinates->x;
            int y = current->coordinates->y;
            offset.x = x*IMAGE_WIDTH;
            offset.y = y*IMAGE_HEIGHT;
            current = current->next;
            SDL_BlitSurface(images[TAIL], NULL, window, &offset);
        }
    }
    if (get_nr_of_snakes() == 2) {
        snake = get_snake(2);
        current = get_snake(2)->snakebody;
        if (current!= NULL) {
            while (current->next != NULL) {
                int x = current->coordinates->x;
                int y = current->coordinates->y;
                offset.x = x*IMAGE_WIDTH;
                offset.y = y*IMAGE_HEIGHT;
                current = current->next;
                SDL_BlitSurface(images[TAIL], NULL, window, &offset);
            }
        }
    }
}
void draw_snake_head(){
    SDL_Rect offset;
    struct Snake snake = * get_snake(1);
    int x = snake.snakebody->coordinates->x;
    int y = snake.snakebody->coordinates->y;
    offset.x = x*IMAGE_WIDTH;
    offset.y = y*IMAGE_HEIGHT;
    
    SDL_BlitSurface(images[TAIL], NULL, window, &offset);
    
    if (get_nr_of_snakes() == 2){
        snake = * get_snake(2);
        int x = snake.snakebody->coordinates->x;
        int y = snake.snakebody->coordinates->y;
        offset.x = x*IMAGE_WIDTH;
        offset.y = y*IMAGE_HEIGHT;
        
        SDL_BlitSurface(images[TAIL], NULL, window, &offset);
    }
}
void draw_grid(int width, int height) {
    
    /*
     * Onderstaande code moet zeker worden uitgevoerd op het einde van deze functie.
     * Wanneer je iets tekent in het venster wordt dit venster nl. niet meteen aangepast.
     * Via de SDL_Flip functie wordt het venster correct geupdatet.
     */
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            if ((get_cell(x, y)->state) == WALL){
                draw_cell(x, y, HEAD);
            }
            else if ((get_cell(x, y)->state) == APPLE){
                draw_cell(x, y, APPLE_TILE);
            }
            else if ((get_cell(x, y)->state) == SPECIAL_FOOD){
                draw_cell(x, y, SPECIAL_TILE);
            }
            else draw_cell(x, y, COVERED);
        }
    }
    draw_snake_head();
    draw_snake_part();
    
    int score = get_score();
    char score_str[10];
    sprintf(score_str, "%d", score);
    
    drawText(window, score_str, 20, 0, 0);
    SDL_Flip(window);
}
void draw_game_over(int width, int height){
    SDL_FillRect(window, NULL,SDL_MapRGB(window->format, 255, 255, 255));
    int score = get_score();
    char score_str[20];
    char highscore_str[20];
    int highscore = get_highscore();
    sprintf(score_str, "Score: %d", score);
    sprintf(highscore_str, "Highscore: %d", highscore);
    drawText(window, score_str, 20, (width/2), height/2);
    drawText(window, highscore_str, 20, (width/2), (height+100)/2);
    SDL_Flip(window);
    
}


void read_input(int width, int height, bool game_running) {
    
    SDL_Event event;
    
    
    /*
     * Handelt alle input uit de GUI af.
     * Telkens de speler een input aan de GUI geeft (bv. een muisklik, muis bewegen, toets indrukken enz.)
     * wordt er een 'event' (van het type SDL_Event) gegenereerd dat hier wordt afgehandeld.
     *
     * Let wel op: niet al deze events zijn relevant voor jou: als de muis bv. gewoon wordt bewogen, hoef
     * je niet te reageren op dit event. Je zal dus (eventueel) een manier moeten vinden om alle niet-relevante
     * events weg te filteren.
     *
     * Zie ook https://wiki.libsdl.org/SDL_PollEvent en http://www.parallelrealities.co.uk/2011_09_01_archive.html
     */
    if (game_running){
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    // De speler wil het spel afsluiten.
                    save_snake_state(height, width);
                    save_apples_state(height, width);
                    if (get_special_active()){
                        save_special_state(height, width);
                    }
                    deallocate_grid(width, height);
                    deallocate_snake(1);
                    deallocate_snake(2);
                    exit(1);
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_UP){
                        change_direction(UP, 1);
                    }
                    else if (event.key.keysym.sym == SDLK_DOWN){
                        change_direction(DOWN, 1);
                    }
                    else if (event.key.keysym.sym == SDLK_RIGHT){
                        change_direction(RIGHT, 1);
                    }
                    else if (event.key.keysym.sym == SDLK_LEFT){
                        change_direction(LEFT, 1);
                    }
                    else if (event.key.keysym.sym == SDLK_p){
                        pause_game();
                    }
                    
                    // Voor een 2e speler
                    else if (event.key.keysym.sym == SDLK_w){
                        if (get_nr_of_snakes() == 1) {
                            allocate_snake(height, width, 2);
                            initialize_snake(width, height, 2);
                        }
                        else{
                            change_direction(UP, 2);
                        }
                    }
                    else if (event.key.keysym.sym == SDLK_s){
                        if (get_nr_of_snakes() == 2) {
                            change_direction(DOWN, 2);
                        }
                    }
                    else if (event.key.keysym.sym == SDLK_d){
                        if (get_nr_of_snakes() == 2){
                            change_direction(RIGHT, 2);
                        }
                    }
                    else if (event.key.keysym.sym == SDLK_a){
                        if (get_nr_of_snakes() == 2) {
                            change_direction(LEFT, 2);
                        }
                    }
                default:
                    // De speler heeft op een andere toets gedrukt.
                    // Deze printf mag je verwijderen.
                    printf("toets ingedrukt\n");
                    
                    break;
            }
        }
    }
    else{
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit(1);
                default:
                    printf("toets ingedrukt\n");
                    break;
            }
        }
    }
}

/*
 * Laadt de afbeeldingen die getoond moeten worden in. Alle afbeeldingen worden samen bijgehouden
 * in een array 'images'.
 */
void initialize_figures() {
    images[APPLE_TILE] =  SDL_LoadBMP("Images/apple.bmp");
    images[HEAD] = SDL_LoadBMP("/Users/alexandre/Dropbox/CW/Structuur2/Snake/Snake/Snake/Images/head.bmp");
    images[TAIL] = SDL_LoadBMP("Images/tail.bmp");
    images[COVERED] = SDL_LoadBMP("Images/covered.bmp");
    images[SPECIAL_TILE] = SDL_LoadBMP("Images/special.bmp");
}
/*
 * Initialiseer het venster.
 */

void initialize_window(char *title, int grid_width, int grid_height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    if (TTF_Init() == -1){
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    int window_width = grid_width * IMAGE_WIDTH;
    int window_height = grid_height * IMAGE_HEIGHT;
    window = SDL_SetVideoMode(window_width, window_height, 0, SDL_HWPALETTE | SDL_DOUBLEBUF);
    if (window == NULL) {
        printf("Couldn't set screen mode to required dimensions: %s\n", SDL_GetError());
        exit(1);
    }
    /* Set the screen title */
    SDL_WM_SetCaption(title, NULL);
    
}

void initialize_gui(int grid_width, int grid_height) {
    initialize_window("Snake", grid_width, grid_height);
    initialize_figures();
    SDL_Event event;
    SDL_PollEvent(&event);
    atexit(stop_gui);
}





