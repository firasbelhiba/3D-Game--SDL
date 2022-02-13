#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include "map.h"
#include <time.h>
SDL_Surface* initMap(SDL_Surface* Background,SDL_Rect* posMap)
{
 	posMap->x = 0;
	posMap->y = 0;
	
	return Background = IMG_Load("map.png");

}

SDL_Surface* initCol(SDL_Surface* collision)
{
	 collision = IMG_Load("collision.png");
	return collision;
}

SDL_Surface* initEntite(SDL_Surface* potion ,SDL_Rect* posPotion)
{

	SDL_Rect Tab[4];
	int i;
	Tab[0].x =1706;
	Tab[0].y =2241; 
	
	Tab[1].x = 3073;
	Tab[1].y = 2028;

	Tab[2].x = 3770;
	Tab[2].y = 1842;
	
	Tab[3].x = 1960;
	Tab[3].y = 1305;

	srand(time(NULL));
	i = rand() %4;	
	
	posPotion->x = Tab[i].x;
	posPotion->y = Tab[i].y;
	
	potion = IMG_Load("potion.png");
	
	posPotion->w = 20;
	posPotion->h = 40;

	return potion;

}
