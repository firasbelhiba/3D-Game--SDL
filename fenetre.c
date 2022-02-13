#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "fenetre.h"
SDL_Surface*  fenetre (SDL_Surface* ecran ,int* SCREEN_HEIGHT,int* SCREEN_WIDTH)
{
	(*SCREEN_HEIGHT) = 768;
	(*SCREEN_WIDTH )= 1228;

	SDL_Init(SDL_INIT_VIDEO);
	
	ecran = SDL_SetVideoMode(*SCREEN_WIDTH,*SCREEN_HEIGHT,32,SDL_HWSURFACE | SDL_DOUBLEBUF);

	return ecran;

}
