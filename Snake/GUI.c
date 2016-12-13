//
//  gui.c
//  Snake
//
//  Created by Alexandre Kahn on 12/12/2016.
//  Copyright © 2016 Alexandre Kahn. All rights reserved.
//

#include "gui.h"
#include "Snake.h"
/*
 * Dit is het venster dat getoond zal worden en waarin het speelveld weergegeven wordt.
 * Dit venster wordt aangemaakt bij het initialiseren van de GUI en wordt weer afgebroken
 * wanneer het spel eindigt.
 */
static SDL_Surface *window;
void stop_gui() {
    SDL_Quit();
}

SDL_Surface* images[4];

void draw_cell(int x, int y, int kleur){
    SDL_Rect offset;
    offset.x = x*IMAGE_WIDTH;
    offset.y = y*IMAGE_HEIGHT;
   
    SDL_BlitSurface(images[kleur], NULL, window, &offset);
    
}
void draw_grid(int width, int height) {
    
    /*
     * Onderstaande code moet zeker worden uitgevoerd op het einde van deze functie.
     * Wanneer je iets tekent in het venster wordt dit venster nl. niet meteen aangepast.
     * Via de SDL_Flip functie wordt het venster correct geupdatet.
     */
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            if ((get_cell(x, y)->state) == APPLE){
            draw_cell(x, y, APPLE_TILE);
            }
            //else draw_cell(x, y, COVERED);
        }
    }
    for (int i = 0; i < snake_length; i++) {
        printf("ok");
    }
    SDL_Flip(window);
}


void read_input(int width, int height) {
    
    SDL_Event event;
    
    int mouse_x;
    int mouse_y;
    
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
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                // De speler wil het spel afsluiten.
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_p:
                        // De speler heeft op de P toets gedrukt.
                    default:
                        // De speler heeft op een andere toets gedrukt.
                        // Deze printf mag je verwijderen.
                        printf("toets ingedrukt\n");
                }
                break;
                
            case SDL_MOUSEBUTTONDOWN:
                /*
                 * De speler heeft met de muis geklikt: met de onderstaande lijn worden de coördinaten in het
                 * het speelveld waar de speler geklikt heeft bewaard in de variabelen mouse_x en mouse_y.
                 */
                SDL_GetMouseState(&mouse_x, &mouse_y);
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        draw_grid(width, height);
                        // De gebruiker heeft met de linkermuisknop geklikt.
                    case SDL_BUTTON_RIGHT:
                        // De gebruiker heeft met de rechtermuisknop geklikt.
                        // Deze printf mag je verwijderen.
                        printf("muis geklikt\n");
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
}
/*
 * Initialiseer het venster.
 */

void initialize_window(char *title, int grid_width, int grid_height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
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
    draw_grid(grid_width, grid_height);
    atexit(stop_gui);
}





