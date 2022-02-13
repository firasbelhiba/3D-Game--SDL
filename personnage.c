#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "personnage.h"

SDL_Surface* personnage(SDL_Rect* Personnage,SDL_Surface* sprite)
{

	sprite = IMG_Load("sprite.png");

	Personnage-> x = 2000;
	Personnage-> y = 3090;

return sprite;
}

