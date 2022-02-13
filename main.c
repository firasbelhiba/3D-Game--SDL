/**
*@file main.c
*@author Nebil
*
*/
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "jeu.h"
#include "menu.h"
#include "fenetre.h"
#include "map.h"
#include "personnage.h"
#include "scrolling.h"
#include "boundBox.h"
#include "sauvegarde.h"

int main()

{
SDL_Surface *ecran;
int SCREEN_WIDTH ,SCREEN_HEIGHT ; 
int continuer = 1;
ecran = fenetre(ecran,&SCREEN_HEIGHT,&SCREEN_WIDTH);


int choix = 0;
int sauv = 0;
choix = menu(ecran,&sauv,&continuer);
printf("Jeu lance \n");
if(choix == 1)
{
	jeu(ecran,SCREEN_WIDTH,SCREEN_HEIGHT,sauv);
}

return 0 ;
}
