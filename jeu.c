#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "map.h"
#include "personnage.h"
#include "scrolling.h"
#include "jeu.h"
#include "sauvegarde.h"

void jeu(SDL_Surface* ecran,int  SCREEN_WIDTH,int SCREEN_HEIGHT,int sauv)
{

SDL_Surface  *background = NULL, *perso = NULL, *mapCollision = NULL, *potion = NULL;
SDL_Rect posMap, camera, posPerso, posPotion;
save partie;
background = initMap(background,&posMap);
mapCollision = initCol(mapCollision);

perso = personnage(&posPerso,perso);		// INITIALISATION
potion = initEntite(potion,&posPotion);
if(sauv)
{
	partie = Load();

	posPerso = partie.posSprite;
	posPotion = partie.posEntite;
	
}


scrolling(SCREEN_WIDTH,SCREEN_HEIGHT,ecran,background,perso,posPerso,posMap,mapCollision,posPotion,potion,partie,sauv); //SCROLLING

return;
}
