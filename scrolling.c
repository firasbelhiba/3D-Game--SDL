/**
*@file scrolling.c
*@author Nebil
*
*/
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include "scrolling.h"
#include <string.h>
#include <SDL/SDL_ttf.h>
#include "boundBox.h"
#include <time.h>
#include "sauvegarde.h"

/**
*@author internet
*@brief saisir un pixel bien defini
*@param surface image de laquelle on saisit le pixel
*@param x coordonne du pixel
*@param y coordonne du pixel
*/
Uint32 obtenirPixel(SDL_Surface *surface, int x, int y)
{
    /*nbOctetsParPixel représente le nombre d'octets utilisés pour stocker un pixel.
    En multipliant ce nombre d'octets par 8 (un octet = 8 bits), on obtient la profondeur de couleur
    de l'image : 8, 16, 24 ou 32 bits.*/
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    /* Ici p est l'adresse du pixel que l'on veut connaitre */
    /*surface->pixels contient l'adresse du premier pixel de l'image*/
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;

    /*Gestion différente suivant le nombre d'octets par pixel de l'image*/
    switch(nbOctetsParPixel)
    {
        case 1:
            return *p;
	break;

        case 2:
            return *(Uint16 *)p;
	break;

        case 3:
            /*Suivant l'architecture de la machine*/
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
	break;

        case 4:
            return *(Uint32 *)p;
	break;

        /*Ne devrait pas arriver, mais évite les erreurs*/
        default:
            return 0;
    }
}

/**
*@author wael
*@brief detect les colisions avec le background
*@param poschar position du personnage
*@param mapenigme Background sur lequelle on test les collisions
*/
int Collision(SDL_Rect poschar, SDL_Surface *mapenigme, SDL_Surface *ecran, int mouvement)
{
	SDL_Surface *blanc = NULL, *gris = NULL, *rouge = NULL;
	SDL_Rect positionCouleur;

	Uint32 rouger,blancr,grisr,temp;
	Uint8 r,v,b,a;

	positionCouleur.x = 0;
	positionCouleur.y = 0;

	blanc = IMG_Load("blanc.png");
	gris = IMG_Load("gris.png");
	rouge = IMG_Load("rouge.png");

	/*SDL_BlitSurface(blanc, NULL, ecran, &positionCouleur);
	SDL_BlitSurface(gris, NULL, ecran, &positionCouleur);
	SDL_BlitSurface(rouge, NULL, ecran, &positionCouleur);
	SDL_Flip(ecran);*/

	blancr = obtenirPixel(blanc,1,1);
	grisr = obtenirPixel(gris,1,1);
	rouger = obtenirPixel(rouge,1,1);

	SDL_FreeSurface(blanc);
	SDL_FreeSurface(gris);
	SDL_FreeSurface(rouge);

	temp = obtenirPixel(mapenigme,15+poschar.x+(poschar.w)/2,70+poschar.y+(poschar.h)/2);

	SDL_GetRGBA(temp, mapenigme->format, &r, &v, &b, &a);

        if ((r == 255)&&(v == 255)&&(b == 255))
	{
           return 0;
       	}

       	else if ((r == 170)&&(v == 170)&& ((b == 171)||(b == 170)))
        {
           return 0;
        }

	else if ((r == 255)&&(v == 0)&&(b == 0))
	{
	   return 1;
	}
	else
	{
	
		return -1;
	}
}

int afficherEnigme(Enigme e, SDL_Surface* ecran, int niveau, int *ex, int *cmp, int *min)
{
*ex=1;
	SDL_Surface *enigme = NULL;
	SDL_Rect positionEnigme[4][4];
	SDL_Rect aux;
	SDL_Event event;
	int i,j,test;
	int res=0;
	int espacex=0;
	int espacey=0;
	Enigme e1;
	int tempsActuel2 = 0, tempsPrecedent2 = 0;

	enigme = IMG_Load(e.nomimage);

	for(i=0; i<niveau; i++)
        {
                for(j=0; j<niveau; j++)
                {
                        e.tab[i][j].x = ((enigme->w)/niveau)*j;
			e.tab[i][j].y = ((enigme->h)/niveau)*i;
			e.tab[i][j].h = ((enigme->h)/niveau);
			e.tab[i][j].w = ((enigme->w)/niveau);

                }
        }

	for(i=0; i<niveau; i++)
        {
                for(j=0; j<niveau; j++)
                {
                        e1.tab[i][j] = e.tab[j][i];
                }
        }

	for(i=0; i<niveau; i++)
	{
		for(j=0; j<niveau; j++)
		{
			if (i != 0)
			{
				espacey = 2;
			}

			if (j != 0)
			{
				espacex = 2;
			}

			positionEnigme[i][j].x = ecran->w/2 - enigme->w/2 + espacex*j + (enigme->w/niveau)*j;
			positionEnigme[i][j].y = ecran->h/2 - enigme->h/2 + espacey*i + (enigme->h/niveau)*i;
		}
	}

	while(res==0)
	{
		tempsActuel2 = SDL_GetTicks();

		if (tempsActuel2 - tempsPrecedent2 >= 1000)  //elwa9te ely t3ada  1000 millisecondes = 1 seconde
		{
		    (*cmp)++;   

		    if((*cmp) ==60)
		    {
		       (*cmp)=0;
		       (*min)++;
		    }

		    tempsPrecedent2 = tempsActuel2; /* update */
	 
		}
		
		SDL_WaitEvent(&event);

		switch(event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				switch(event.button.button)
				{
					case SDL_BUTTON_LEFT:
						if ((event.button.x >= positionEnigme[0][0].x) && (event.button.x <= positionEnigme[0][0].x + 							     enigme->w) && (event.button.y >= positionEnigme[0][0].y) && 
							(event.button.y <= positionEnigme[0][0].y + enigme->h))
						{
							for(i=0; i<niveau; i++)
							{	
								for(j=0; j<niveau; j++)
								{
									if ((event.button.x>=positionEnigme[i][j].x)&&			  										    (event.button.x<=positionEnigme[i][j].x+(enigme->w)/niveau)&&
									    (event.button.y>=positionEnigme[i][j].y)&&
									    (event.button.y<=positionEnigme[i][j].y+(enigme->h)/niveau))	
									{
										aux = e1.tab[i][j];
										e1.tab[i][j] = e1.tab[1][1];
										e1.tab[1][1] = aux;
									}
								}
							}
						}
						
					break;
				}
			break;
		}
		
		for(i=0; i<niveau; i++)
		{
			for(j=0; j<niveau; j++)
			{
				SDL_BlitSurface(enigme, &e1.tab[i][j], ecran, &positionEnigme[i][j]);
				SDL_Flip(ecran);
			}
		}

		test = 1;

		for(i=0; i<niveau; i++)
		{	
			for(j=0; j<niveau; j++)
			{
				if ((e1.tab[i][j].x == e.tab[i][j].x)&&(e1.tab[i][j].y == e.tab[i][j].y))
				{
					test = 1;
				}
				else
				{
					test = 0;
				}
				
				if (test == 0)
				{
					break;
				}
			}

			if (test == 0)
				{
					break;
				}
		}
		if (test == 1)
		{
			res = 1;
		}
		else
		{
			res = 0;
		}
	}
*ex=2;
	return res;
}
/**
*@author wael
*@brief Generer l'image de l'enigme random
*@param nomfichier Nom du fichier contenant le nom des images
*@return chaine
*/ 
Chaine genererEnigmeRandom(char nomfichier[])
{
	Chaine c;
	FILE *f = NULL;
	int i,j;

	f = fopen(nomfichier,"r");
	if (f != NULL)
	{
		srand(time(NULL));
		i = rand() % 20;

		for (j=0;j<i+1;j++)
		{
			fscanf(f,"%s\n",c.name);
		}
	}

	fclose(f);

	return c;
}

int arduinoWriteData(int x)
{
    char chemin[]="/dev/ttyACM0";
    FILE*f;

    f=fopen(chemin,"w");
    if(f == NULL)
        return(-1);

    fprintf(f,"%d",x);
    fclose(f);

    return(0);
}

int arduinoReadData(int *x)
{
    char chemin[]="/dev/ttyACM0";
    FILE*f;
    char c;
    f=fopen(chemin,"r");

    if(f == NULL)
        return(-1);

    fscanf(f,"%d",x);

    fclose(f);

    return(0);
}
/**
*@author Nebil Nadhir
*@brief Scrolling of the map 
*@param colli Map pour tester la collision parfaite
*@param point image personnage
*@param partie sauvegarde d'une ancienne partie
*@param posMap coordonées de la map
*@param posPers coordonées du personnage
*@param SCREEN_WIDTH largeur de la fenetre
*@param SCREEN_HEIGHT hauteur de la fenetre
*@param ecran fenetre SDL
*@param background Image de la map
*@return nothing
*/
void scrolling(int SCREEN_WIDTH,int SCREEN_HEIGHT,SDL_Surface* ecran,SDL_Surface* background,SDL_Surface* point,SDL_Rect posPers,SDL_Rect posMap,SDL_Surface* colli,SDL_Rect posPotion,SDL_Surface* potion,save partie,int sauv)
{
	int tempsActuel = 0 , tempsPrecedent = 0, ex = 0 ;

	Uint32 prochain_rendu=0;
	int i = 0 , j , xx , yy ;
	SDL_Rect poscharix ;
	
	int collision,auxcolli=0;
	int res=0;
	Enigme e;
	Chaine nomenigme;
//temps
	SDL_Surface *texte = NULL;
	TTF_Font *police = NULL;
	SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255};
	char temps[20] = "3:00" ; 
	int tempsActuel2 = 0, tempsPrecedent2 = 0, sec = 0, cmp = 0,min = 0,k,t;
	SDL_Rect position_text;
	position_text.x=SCREEN_WIDTH /2;
	position_text.y=0;
	TTF_Init();//initialiser ttf
    	police = TTF_OpenFont("angelina.ttf", 30);//Chargement de la police
	//sprintf(temps, "Temps : %d", cmp);
    	texte = TTF_RenderText_Shaded(police, temps,couleurBlanche, couleurNoire);
	SDL_BlitSurface(texte, NULL, ecran, &position_text);

//manette
	int receive=0;
	SDL_Surface *Fond = NULL, *Yes = NULL, *No = NULL;
	SDL_Rect positionFond, positionYes, positionNo;

	Fond = IMG_Load("Fond.png");
	positionFond.x = ecran->w/2 - Fond->w/2;
	positionFond.y = ecran->h/2 - Fond->h/2;

	positionYes.x = positionFond.x + 50;
	positionYes.y = positionFond.y + 90;

	positionNo.x = positionYes.x;
	positionNo.y = positionYes.y + 80;
	int pause = 0;
	

	
        Yes = IMG_Load("YES.png");
        No = IMG_Load("NO.png");


	SDL_Event event;
	SDL_Rect sprite ;
		
	SDL_Rect BoxPlayer;
	const int POINT_WIDTH = point->w ;
	const int POINT_HEIGHT = point->h;
	int test = 0;
	int xVel = 0;
	int yVel = 0; //vitesse
	int vitesse = 1;
	int x = posPers.x; //coordonne du point
	int y = posPers.y;
	int collBox = 0;
	int game = 1;
	SDL_Rect camera ={x,y,SCREEN_WIDTH,SCREEN_HEIGHT};
	
	const int LEVEL_HEIGHT = background->h;
	const int LEVEL_WIDTH = background->w;

	int xPot = posPotion.x;
	int yPot = posPotion.y;

	int frame = 0, status = 0,mv = 0;
	SDL_Rect posSprite[4][3];
	SDL_Rect BoxPotion;
	BoxPotion.x = xPot;
	BoxPotion.y = yPot;
	BoxPotion.w = posPotion.w;
	BoxPotion.h = posPotion.h;
	if(sauv == 1)
	{
		cmp = partie.s;
		min = partie.m;
	}
	for(k=0;k<4;k++)
	{
		for(t=0;t<3;t++)
		{
			posSprite[k][t].x = point->w/3*t;
			posSprite[k][t].y = point->h/4*k;
			posSprite[k][t].h = point->h/4;
			posSprite[k][t].w = point->w/3;
		}

	}

	
	while(game)
	{

	if(pause == 0)
	{
	tempsActuel2 = SDL_GetTicks();
	if (tempsActuel2 - tempsPrecedent2 >= 1000)  //elwa9te ely t3ada  1000 millisecondes = 1 seconde
        {
            cmp++;   
 
            if(cmp ==60)
            {
               cmp=0;
               cmp++;
           	min++;
	    }
	

	if(60 - cmp < 10)
	{
		sprintf(temps,"0%d : 0%d",20 - min,60 - cmp);
	}
	else
	{
		sprintf(temps,"%d : %d",20 - min,60 - cmp);
	}
	 /* On écrit dans la chaîne "temps" le nouveau temps */
        SDL_FreeSurface(texte); 
        texte = TTF_RenderText_Shaded(police, temps,couleurBlanche,couleurNoire);
        tempsPrecedent2 = tempsActuel2; /* update */		 
	}
	}
	if((min == 20))
	{
		game = 0;	
	}



	while(SDL_PollEvent(&event))
	{
			
		switch(event.type)
		{
			
			case SDL_KEYDOWN : 
				
				switch(event.key.keysym.sym)
				{
					case SDLK_UP:
						if(ex==0){
						yVel = -2;
						xVel = 4 ;
						mv = 1;
						j=1;
						i=1;
						}
						break;
					case SDLK_DOWN:
						if(ex==0){
						yVel = 2;
						xVel = -4;
						mv = 2;
						j=2;
						i=1;}	
						break;
					case SDLK_RIGHT:		//Icrement la vitesse
						if(ex==0){
						xVel = 4;
						yVel = 2;
						mv = 3;
						j=3;
						i=1;}
						break;
					case SDLK_LEFT :
						if(ex==0){
						xVel = -4 ;
						yVel = -2;
						mv = 4;
						j=4;
						i=1;}
						break;
					case SDLK_ESCAPE:
						SDL_BlitSurface(Fond,NULL,ecran,&positionFond);
						SDL_BlitSurface(Yes,NULL,ecran,&positionYes);
						SDL_BlitSurface(No,NULL,ecran,&positionNo);
						pause = 1;
					break;
				}
				break;
			case SDL_KEYUP : 
				switch(event.key.keysym.sym)
				{
					case SDLK_UP : 
						i=0;
						if(ex==0){
						yVel += 2;
						xVel -= 4;
						mv = 0;
						}
						break;
					case SDLK_DOWN : 
						i=0;
						if(ex==0){
						mv = 0;
						yVel -= 2;
						xVel += 4;
						}
						break;
					case SDLK_RIGHT : 
						i=0;		//EVITER SDL_keyrepeat
						if(ex==0){
						mv = 0;	
						xVel -=4 ;
						yVel -= 2 ;
						}
						break;
					case SDLK_LEFT : 
						i=0;
						if(ex==0){
						mv = 0;
						xVel += 4;
						yVel += 2;
						}
						break;
						
				}
				break;
			case SDL_MOUSEBUTTONDOWN: 
			switch(event.button.button)
		        {	
				    case SDL_BUTTON_LEFT:
				
						if(event.button.x>positionYes.x &&
						event.button.x<positionYes.x + Yes->w &&
						event.button.y>positionYes.y &&
						event.button.y<positionYes.y + Yes->h && pause)
						{
							posPers.y = y;
							posPers.x = x;
							posPotion.x += camera.x;
							posPotion.y += camera.y;	
		                                      sauvegarde(posPers,min,cmp,posPotion);
							game =0;
						}
					
						if(event.button.x>positionNo.x&&
						event.button.x<positionNo.x + No->w&&
						event.button.y>positionNo.y&&
						event.button.y<positionNo.y + No->h && pause)
						{
							game = 0;
						

						}
					break;
				
			}
			break;
			/*if(ex==0)switch(event.button.button)
		        {
		            case SDL_BUTTON_LEFT:
				{
					xx = event.button.x - posPers.x ;
					yy = event.button.y - posPers.y ;
					i=1;			
					if(yy<=0&&ex==0)
					{ //up
						yVel  = -2;
						xVel  = 4;
						mv = 1;
						j=1;
					}
					else if(yy>=75&&ex==0)
					{ //down
						yVel += 2;
						xVel = -4;
						mv = 2;
						j=2;
					}
					else if(xx>=30&&ex==0)
					{ //right
						xVel = 2 +2;
						yVel = 2;
						 mv = 3;
						j=3;
					}
					else if(xx<=0&&ex==0)
					{ //left
						xVel = -4 ;
						yVel = -2;
						mv = 4;
						j=4;
					}

				}
		                break;
		        }
		        break;
			
			case SDL_MOUSEBUTTONUP: 
			if(ex==0)switch(event.button.button)
		        {
		            case SDL_BUTTON_LEFT:
				{
					xx = event.button.x - posPers.x ;
					yy = event.button.y - posPers.y ;
					i=0;			
					if(yy<=0&&ex==0&&j!=1)
					{ //up
						yVel += 2;
						xVel -= 2 + 2;
						
					}
					else if(yy>=75&&ex==0&&j!=1)
					{ //down
						yVel -= 2;
						xVel += 2 + 2;
						;
					}
					else if(xx>=30&&ex==0&&j!=1)
					{ //right
						xVel -= 2 +2;
						yVel -= 2;
						
					}
					else if(xx<=0&&ex==0&&j!=1)
					{ //left
						xVel += 2 + 2 ;
						yVel += 2;
						
					}

				}
		                break;
		        }
		        break;*/
		}
		
		if(event.type == SDL_QUIT)
		{
			game = 0;
		}
	}
			
			
			x+=xVel ;
			y+=yVel ;
			
			poscharix.x = x;
			poscharix.y = y;

			collision = Collision(poscharix, colli, ecran, 1);
		 
			if((x<0) ||(x + POINT_WIDTH > LEVEL_WIDTH) || ((collision != 0)&&(auxcolli == 0)))
			{
				x-=xVel;	
			}	

			
			if((y<0) ||(y + POINT_HEIGHT >LEVEL_HEIGHT) || ((collision != 0)&&(auxcolli == 0)))
			{
				y-=yVel;
			}

			camera.x = (x + POINT_WIDTH /2) - SCREEN_WIDTH /2;		//Centrez la camera sur le point
			camera.y = (y + POINT_WIDTH /2) - SCREEN_HEIGHT /2;

			if ( collision == 0 )
			{	
				auxcolli = 0;
				if(ex==2)
				{
					i=0;
					ex=0;
					if(status==0){
						 yVel += 2;
						 xVel -= 2 + 2;
					}
					else if(status==1){
						yVel -= 2;
						xVel += 2 + 2;
					}
					else if(status==2){
						yVel -= 2;
						xVel -= 2 + 2;
					}
					else {
						yVel += 2;
						xVel += 2 + 2;
					}
					mv = 0;	
				}
			}			


			if(camera.x < 0)
			{
				camera.x = 0;
			}
			if(camera.y < 0)
			{
				camera.y = 0;
			}
			if(camera.x >LEVEL_WIDTH - camera.w)		// Empeche la camera de deborder
			{
				camera.x = LEVEL_WIDTH - camera.w;
			}
			if(camera.y >LEVEL_HEIGHT- camera.h)
			{
				camera.y = LEVEL_HEIGHT - camera.h;
			}

			posPers.x = x - camera.x;	//coordoné du point relatifs a la camera
			posPers.y = y - camera.y; 	
		
		
		if(mv == 1)
		{
			if(tempsActuel-prochain_rendu >=120)
			{
			prochain_rendu = tempsActuel;
			status = 0;
			frame ++;
			}
		}
		else if (mv == 2)
		{
			if(tempsActuel-prochain_rendu >=120)
			{
			prochain_rendu = tempsActuel;
			status = 1;
			frame ++;
			}
		}
		else if(mv == 3)
		{
			if(tempsActuel-prochain_rendu >=120)
			{
			prochain_rendu = tempsActuel;
			status = 2;
			frame ++;
			}
		}
		else if(mv == 4)
		{
			if(tempsActuel-prochain_rendu >=120)
			{
			prochain_rendu = tempsActuel;
			status = 3;
			frame ++;
			}
		}
		else
		{
			frame = 0;
		}

		if(frame>2)
		{
			frame = 0;
		}

		if (collision == 1)
			{
				nomenigme = genererEnigmeRandom("random.txt");
				printf("%s\n",nomenigme.name);

				strcpy(e.nomimage,nomenigme.name);
				
				res = 0;
				
				if (auxcolli == 0)
				{	
					res = afficherEnigme(e, ecran, 3,&ex,&cmp,&min);
					if (res == 1)
					{
						auxcolli = 1;
					}
					else
					{
					i=0;
					ex=0;
						if(status==0){
							yVel += 2;
							xVel -= 2 + 2;
						}
						else if(status==1){
							yVel -= 2;
							xVel += 2 + 2;
						}
						else if(status==2){
							yVel -= 2;
							xVel -= 2 + 2;
						}
						else {
							yVel += 2;
							xVel += 2 + 2;
						}
						mv = 0;	
					}
				}
			}


		BoxPlayer.y = y ;
		BoxPlayer.x = x ;
		BoxPlayer.w = 30;
		BoxPlayer.h = 70;
		
			
		posPotion.x = xPot - camera.x;
		posPotion.y = yPot - camera.y;
	
		if(pause == 0)
		{	
		SDL_BlitSurface(background,&camera,ecran,&posMap);
	
		if(collBox == 0)
		{
			collBox = boundBox(BoxPlayer,BoxPotion);
			SDL_BlitSurface(potion,NULL,ecran,&posPotion);

		}
		else
		{
			game = 0;
		}
		
		SDL_BlitSurface(point,&posSprite[status][frame],ecran,&posPers);

		SDL_BlitSurface(texte, NULL, ecran, &position_text);
		}
		SDL_Flip(ecran);	
	
		tempsActuel = SDL_GetTicks();
		
		if(tempsActuel - tempsPrecedent < 30 )
		{
			SDL_Delay(30 - (tempsPrecedent - tempsPrecedent));
		}
		else								//framerate
		{
			tempsPrecedent = tempsActuel;	
		}
	
		
		
	}
SDL_FreeSurface(background);
SDL_FreeSurface(ecran);
SDL_FreeSurface(point);
SDL_FreeSurface(potion);
SDL_FreeSurface(Fond);
SDL_FreeSurface(Yes);
SDL_FreeSurface(No);
SDL_Quit();
return;
}
