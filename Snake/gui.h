#ifndef GUI_H_
#define GUI_H_

#include "SDL/SDL.h"

/*
 * De hoogte en breedte (in pixels) van de afbeeldingen die getoond worden.
 * Als je andere afbeelding wil gebruiken in je GUI, zorg er dan voor dat deze
 * dimensies ook aangepast worden.
 */
#define IMAGE_HEIGHT 50
#define IMAGE_WIDTH 50

/*
 * Initialiseert onder andere het venster waarin het speelveld getoond zal worden.
 * Deze functie moet dus aangeroepen worden aan het begin van het spel, vooraleer je
 * het speeldveld begint te tekenen.
 *
 * De functie neemt als argumenten ook de breedte en de hoogte van het speelveld.
 */
void initialize_gui(int grid_width, int grid_height);

/*
 * Tekent het huidige veld in het venster. Deze functie moeten jullie dus zelf implementeren.
 */
//void draw_grid(void);

#endif /* GUI_H_ */
