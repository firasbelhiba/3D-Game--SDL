/**
*@file sauvegarde.c
*@author khairi
*@brief Sauvegarde et chargement d'une partie
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "sauvegarde.h"

void sauvegarde(SDL_Rect posPers,int min,int sec,SDL_Rect posPotion)
{
	FILE* f;
	f=fopen("save.bin","wb");
	save Partie;
	Partie.m = min;
	Partie.s = sec;
	Partie.posSprite = posPers;
	Partie.posEntite = posPotion;
	fwrite(&Partie,sizeof(Partie),1,f);
	fclose(f);
	return;
}

save Load()
{
	save S;
	FILE* f;
	f = fopen("save.bin","rb");
	if(f == NULL)
	{
	
		printf("ERREUR");
		
	}

	fread(&S,sizeof(S),1,f);
	fclose(f);
	return S;
}
