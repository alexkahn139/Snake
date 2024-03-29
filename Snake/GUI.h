#ifndef GUI_H_
#define GUI_H_

#include "SDL/SDL.h"
#include "SDL_ttf.h"
#include <stdbool.h>
#include "grid.h"
#include "snake.h"
#include "inputoutput.h"


/*
 * De hoogte en breedte (in pixels) van de afbeeldingen die getoond worden.
 * Als je andere afbeelding wil gebruiken in je GUI, zorg er dan voor dat deze
 * dimensies ook aangepast worden.
 */
#define IMAGE_HEIGHT 10
#define IMAGE_WIDTH 10

/*
 * Initialiseert onder andere het venster waarin het speelveld getoond zal worden.
 * Deze functie moet dus aangeroepen worden aan het begin van het spel, vooraleer je
 * het speeldveld begint te tekenen.
 *
 * De functie neemt als argumenten ook de breedte en de hoogte van het speelveld.
 */
void initialize_gui(int grid_width, int grid_height);
void read_input(int width, int height, bool game_running);
/*
 * Tekent het huidige veld in het venster. Deze functie moeten jullie dus zelf implementeren.
 */
void draw_grid(int width, int height);
void draw_game_over(int width, int height);
enum Type_bitmap{
    APPLE_TILE,
    HEAD,
    TAIL,
    COVERED,
    SPECIAL_TILE
};
#endif /* GUI_H_ */
