#ifndef SAUVEGARDE_H_
#define SAUVEGARDE_H_
/**
*@struct save
*@brief structure pour sauvegarder
*/
typedef struct save save;
struct save
{
	SDL_Rect posSprite;/*!<position du personnage*/
	int m;	/*!< les minutes du compteur*/
	int s;	/*!< les secondes du compteur*/
	SDL_Rect posEntite;	/*!< position de l'entite secondaire(potion) */
	

};
void sauvegarde(SDL_Rect posPers,int min,int sec,SDL_Rect posPotion);
save Load();

#endif /* SAUVEGARDE_H_ */
