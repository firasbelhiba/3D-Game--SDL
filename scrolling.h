#ifndef SCROLLING_H_
#define SCROLLING_H_
#include "sauvegarde.h"
typedef struct move move;
struct move
{
	int up,down,right,left;
};

typedef struct Enigme Enigme;
struct Enigme
{
	SDL_Rect tab[4][4];
	char nomimage[30];
};

typedef struct Chaine Chaine;
struct Chaine
{
	char name[30];
};

void scrolling(int SCREEN_WIDTH,int SCREEN_HEIGHT,SDL_Surface* ecran,SDL_Surface* background,SDL_Surface* point,SDL_Rect posPerso,SDL_Rect posMap,SDL_Surface* colli,SDL_Rect posPotion,SDL_Surface* potion,save partie,int sauv);
Uint32 obtenirPixel(SDL_Surface *surface, int x, int y);
int Collision(SDL_Rect poschar, SDL_Surface *mapenigme, SDL_Surface *ecran, int mouvement);
int afficherEnigme(Enigme e, SDL_Surface* ecran, int niveau, int *ex, int *cmp, int *min);
Chaine genererEnigmeRandom(char nomfichier[]);
#endif
