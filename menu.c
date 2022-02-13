#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "menu.h"

void pause();

int menu(SDL_Surface* ecran,int* sauv,int* contimenu)
{
	SDL_Surface  *image = NULL ,*image1=NULL, *imagepng = NULL ;//creer une surface pour creer une fenetre
	SDL_Surface *texte = NULL , *btn_play = NULL , *btn_options = NULL , *btn_quit = NULL , *ON = NULL , *OFF=NULL  ,  *level1=NULL , *level2=NULL , *level3=NULL , *RETURN=NULL , *LOAD=NULL,*NEWGAME=NULL ;
	int interieur=0 , interieur2 = 0 , firas=0 ;

 
	
	//ouvrir fenetre vide
	
	//ecran  = SDL_SetVideoMode(1200,768,32, SDL_HWSURFACE | SDL_DOUBLEBUF);//creer une fenetre (SDL_RESIZABLE/SDL_NOFRAME/SDL_FULLSCREEN)
	// creer titre de la fenetre

	//SDL_FillRect(ecran , NULL,SDL_MapRGB(ecran->fo

	
	SDL_Rect position_fond;//creer une position de l image
	position_fond.x=0;
	position_fond.y=0;
	image = IMG_Load("background1.png");//chargement de l image
	SDL_BlitSurface(image,NULL,ecran,&position_fond);
		
	SDL_Rect position_btn_play;//creer une position de l image
	position_btn_play.x=500;
	position_btn_play.y=250;
	btn_play = IMG_Load("btn_play.png");
	SDL_BlitSurface(btn_play,NULL,ecran,&position_btn_play);

	SDL_Rect position_btn_options;//creer une position de l image
        position_btn_options.x=500;
        position_btn_options.y=350;
        btn_options = IMG_Load("btn_options.png");
        SDL_BlitSurface(btn_options,NULL,ecran,&position_btn_options);

	SDL_Rect position_btn_quit;//creer une position de l image
        position_btn_quit.x=500;
        position_btn_quit.y=450;
        btn_quit = IMG_Load("btn_quit.png");
        SDL_BlitSurface(btn_quit,NULL,ecran,&position_btn_quit);

SDL_Rect position_ON;//creer une position de l image
        position_ON.x=500;
        position_ON.y=220;
        
     SDL_Rect position_OFF;//creer une position de l image
        position_OFF.x=760;
        position_OFF.y=220; 

SDL_Rect position_level1;//creer une position de l image
        position_level1.x=500;
        position_level1.y=310;

SDL_Rect position_level2;//creer une position de l image
        position_level2.x=760;
        position_level2.y=310;

SDL_Rect position_level3;//creer une position de l image
        position_level3.x=630;
        position_level3.y=380;

SDL_Rect position_RETURN;//creer une position de l image
        position_RETURN.x=1000;
        position_RETURN.y=600;

SDL_Rect position_LOAD;//creer une position de l image
        position_LOAD.x=500;
        position_LOAD.y=350;

SDL_Rect position_NEWGAME;//creer une position de l image
        position_NEWGAME.x=500;
        position_NEWGAME.y=250;






	//gerer le son
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
	   {
	      return EXIT_SUCCESS;
	   }
	Mix_AllocateChannels(10); // jouer un maximum de 10 sons en même temps,
   	Mix_Volume(1, MIX_MAX_VOLUME); //Mettre à mi-volume le post 1
   	Mix_Chunk *son;//Créer un pointeur pour stocker un .WAV
	son = Mix_LoadWAV("pan.wav"); //Charger un wav dans un pointeur
	Mix_VolumeChunk(son, MIX_MAX_VOLUME); //Mettre un volume pour ce wav


Mix_Music *musique;
	musique = Mix_LoadMUS("a.mp3");
	Mix_VolumeMusic(MIX_MAX_VOLUME);
	Mix_PlayMusic(musique , -1);



	//gerer les evenements du clavier et souris
	int continuer=1;
	SDL_Event event;
	SDL_EnableKeyRepeat(10, 10); /* Activation de la répétition des touches */
image1=IMG_Load("background12.png");
RETURN = IMG_Load("RETURN.png");
ON = IMG_Load("ON.png");
OFF = IMG_Load("OFF.png");
level1 = IMG_Load("1.png");
level2 = IMG_Load("2.png");
level3 = IMG_Load("3.png");
LOAD = IMG_Load("LOAD.png");
NEWGAME = IMG_Load("NEWGAME.png");	   
 while (continuer)
	    {
		SDL_WaitEvent(&event);
		switch(event.type)
		{
		    case SDL_QUIT:
		        continuer = 0;
		        break;
		    case SDL_KEYDOWN:
		        switch(event.key.keysym.sym)
		        {
		            case  SDLK_UP:
              
		                break;
		            case SDLK_DOWN:
		                
		                break;
		            case SDLK_RIGHT:
		                
		                break;
		            case SDLK_LEFT:
		                
		                break;
		        }
		        break;
		     case SDL_MOUSEMOTION:
		                if((event.motion.x>=position_btn_play.x +27 && event.motion.x <= position_btn_play.x+220-27 && event.motion.y>=position_btn_play.y+22 && event.motion.y<=position_btn_play.y+98-22)&&interieur==0)
		                {
		                        btn_play = IMG_Load("btn_play_touched.png");
					interieur=1;

		                }
				if((event.motion.x>=position_btn_options.x+27 && event.motion.x <= position_btn_options.x+220-27 && event.motion.y>=position_btn_options.y+22 && event.motion.y<=position_btn_options.y+98-22)&&interieur==0)
		                {
		                        btn_options = IMG_Load("btn_options_touched.png");
					interieur=2;

	

		                }
				if((event.motion.x>=position_btn_quit.x+27 && event.motion.x <= position_btn_quit.x+220-27 && event.motion.y>=position_btn_quit.y+22 && event.motion.y<=position_btn_quit.y+98-22)&&interieur==0)
		                {
		                        btn_quit = IMG_Load("btn_quit_touched.png");
					interieur=3;

		                }
				if(!(event.motion.x>=position_btn_play.x+27 && event.motion.x <= position_btn_play.x+220-27 && event.motion.y>=position_btn_play.y+22 && event.motion.y<=position_btn_play.y+98-22)
&&!(event.motion.x>=position_btn_options.x+27 && event.motion.x <= position_btn_options.x+220-27 && event.motion.y>=position_btn_options.y+22 && event.motion.y<=position_btn_options.y+98-22)
&&!(event.motion.x>=position_btn_quit.x+27 && event.motion.x <= position_btn_quit.x+220-27 && event.motion.y>=position_btn_quit.y+22 && event.motion.y<=position_btn_quit.y+98-22)
&&interieur!=0)
		                {
		                        if(interieur==1)btn_play = IMG_Load("btn_play.png");
					if(interieur==2)btn_options = IMG_Load("btn_options.png");
					if(interieur==3)btn_quit = IMG_Load("btn_quit.png");
					interieur=0;

		                }
		        break; 

		     case SDL_MOUSEBUTTONDOWN: 
			switch(event.button.button)
		        {
		            case SDL_BUTTON_LEFT:
				{
					if((event.button.x>=position_btn_play.x +27 && event.button.x <= position_btn_play.x+220-27 && event.button.y>=position_btn_play.y+22 && event.button.y<=position_btn_play.y+98-22))
		                {
		                        btn_play = IMG_Load("btn_play_clicked.png");
					interieur=4;
					

					Mix_PlayChannel(1, son, 0);//Joue le son 1 sur le canal 1 ; le joue une fois (0 + 1)
		                }
				if((event.button.x>=position_btn_options.x+27 && event.button.x <= position_btn_options.x+220-27 && event.button.y>=position_btn_options.y+22 && event.button.y<=position_btn_options.y+98-22))
		                {
		                        btn_options = IMG_Load("btn_options_clicked.png");

					interieur=5;
					Mix_PlayChannel(1, son, 0);
		                }
				if((event.button.x>=position_btn_quit.x+27 && event.button.x <= position_btn_quit.x+220-27 && event.button.y>=position_btn_quit.y+22 && event.button.y<=position_btn_quit.y+98-22))
		                {
		                        btn_quit = IMG_Load("btn_quit_clicked.png");
					interieur=6;
					Mix_PlayChannel(1, son, 0);

		                }
				}
		                break;
		        }
		        break;

			case SDL_MOUSEBUTTONUP: 
			switch(event.button.button)
		        {
		            case SDL_BUTTON_LEFT:
				{
					if((event.button.x>=position_btn_play.x +27 && event.button.x <= position_btn_play.x+220-27 && event.button.y>=position_btn_play.y+22 && event.button.y<=position_btn_play.y+98-22))
		                {
		                        btn_play = IMG_Load("btn_play.png");
					interieur=7;
firas=0;


while(firas==0)
{
SDL_WaitEvent(&event);
SDL_BlitSurface(image,NULL,ecran,&position_fond);
SDL_BlitSurface(NEWGAME,NULL,ecran,&position_NEWGAME);
SDL_BlitSurface(LOAD,NULL,ecran,&position_LOAD);
SDL_BlitSurface(RETURN,NULL,ecran,&position_RETURN);
SDL_Flip(ecran);
if ((event.button.x>=position_RETURN.x)&&(event.button.x<position_RETURN.x+position_RETURN.w)&&(event.button.y>=position_RETURN.y)&&(event.button.y<position_RETURN.y+position_RETURN.h))
{SDL_BlitSurface(level3,NULL,ecran,&position_level3);
if(event.button.button==SDL_BUTTON_LEFT)
{
Mix_PlayChannel(1, son, 0);
 firas=1;
SDL_Delay(10);

}
}

if ((event.button.x>=position_NEWGAME.x)&&(event.button.x<position_NEWGAME.x+position_NEWGAME.w)&&(event.button.y>=position_NEWGAME.y)&&(event.button.y<position_NEWGAME.y+position_NEWGAME.h))
{
if(event.button.button==SDL_BUTTON_LEFT)
{
Mix_PlayChannel(1, son, 0);
	SDL_FreeSurface(image);
	SDL_FreeSurface(NEWGAME);
	SDL_FreeSurface(LOAD);
	SDL_FreeSurface(RETURN);
	SDL_FreeSurface(btn_play);
	SDL_FreeSurface(btn_quit);
	SDL_FreeSurface(btn_options);
	SDL_FreeSurface(level3);
	SDL_FreeSurface(level2);
	SDL_FreeSurface(level1);

return 1;

}
}

if ((event.button.x>=position_LOAD.x)&&(event.button.x<position_LOAD.x+position_LOAD.w)&&(event.button.y>=position_LOAD.y)&&(event.button.y<position_LOAD.y+position_LOAD.h))
{
if(event.button.button==SDL_BUTTON_LEFT)
{
Mix_PlayChannel(1, son, 0);
	SDL_FreeSurface(image);
	SDL_FreeSurface(NEWGAME);
	SDL_FreeSurface(LOAD);
	SDL_FreeSurface(RETURN);
	SDL_FreeSurface(btn_play);
	SDL_FreeSurface(btn_quit);
	SDL_FreeSurface(btn_options);
	SDL_FreeSurface(level3);
	SDL_FreeSurface(level2);
	SDL_FreeSurface(level1);
	(*sauv) = 1;
	return 1;
}
}








}


		                }
				if((event.button.x>=position_btn_options.x+27 && event.button.x <= position_btn_options.x+220-27 && event.button.y>=position_btn_options.y+22 && event.button.y<=position_btn_options.y+98-22))
		                {
		                        btn_options = IMG_Load("btn_options.png");
					interieur=8;
firas=0;


while(firas==0)
{
SDL_WaitEvent(&event);
SDL_BlitSurface(image1,NULL,ecran,&position_fond);
SDL_BlitSurface(ON,NULL,ecran,&position_ON);
SDL_BlitSurface(OFF,NULL,ecran,&position_OFF);
SDL_BlitSurface(level1,NULL,ecran,&position_level1);
SDL_BlitSurface(level2,NULL,ecran,&position_level2);
SDL_BlitSurface(level3,NULL,ecran,&position_level3);
SDL_BlitSurface(RETURN,NULL,ecran,&position_RETURN);
SDL_Flip(ecran);
if ((event.button.x>=position_RETURN.x)&&(event.button.x<position_RETURN.x+position_RETURN.w)&&(event.button.y>=position_RETURN.y)&&(event.button.y<position_RETURN.y+position_RETURN.h))
{SDL_BlitSurface(level3,NULL,ecran,&position_level3);
if(event.button.button==SDL_BUTTON_LEFT)
{
/*if ((event.motion.x>=position_RETURN.x)&&(event.motion.x<position_RETURN.x+position_RETURN.w)&&(event.motion.y>=position_RETURN.y)&&(event.motion.y<position_RETURN.y+position_RETURN.h))


		                {
		                      SDL_BlitSurface(level3,NULL,ecran,&position_RETURN);  
					
		                }*/
 Mix_PlayChannel(1, son, 0);
 firas=1;
SDL_Delay(10);

}
}

if ((event.button.x>=position_OFF.x)&&(event.button.x<position_OFF.x+position_OFF.w)&&(event.button.y>=position_OFF.y)&&(event.button.y<position_OFF.y+position_OFF.h))
{
if(event.button.button==SDL_BUTTON_LEFT)
{
Mix_PlayChannel(1, son, 0);
Mix_PauseMusic();
// check the music pause status
printf("music is%s paused\n", Mix_PausedMusic()?"":" not");
printf("volume was    : %d\n", Mix_VolumeMusic(MIX_MAX_VOLUME/2));
printf("volume is now : %d\n", Mix_VolumeMusic(-1));
SDL_Delay(10);
}
}


if ((event.button.x>=position_ON.x)&&(event.button.x<position_ON.x+position_ON.w)&&(event.button.y>=position_ON.y)&&(event.button.y<position_ON.y+position_ON.h))
{
if(event.button.button==SDL_BUTTON_LEFT)
{Mix_PlayChannel(1, son, 0);
Mix_ResumeMusic();
SDL_Delay(10);
}
}
}





		                }
				if((event.button.x>=position_btn_quit.x+27 && event.button.x <= position_btn_quit.x+220-27 && event.button.y>=position_btn_quit.y+22 && event.button.y<=position_btn_quit.y+98-22))
		                {
		                        btn_quit = IMG_Load("btn_quit.png");
					interieur=9;

                                        
					SDL_Quit();
		                }
				}
		                break;
		        }
		        break;
		}
		if(interieur!=interieur2)
		{
			interieur2=interieur;
			SDL_BlitSurface(image,NULL,ecran,&position_fond);
			SDL_BlitSurface(btn_play,NULL,ecran,&position_btn_play);
			SDL_BlitSurface(btn_options,NULL,ecran,&position_btn_options);
			SDL_BlitSurface(btn_quit,NULL,ecran,&position_btn_quit);
		}
		SDL_Flip(ecran);
	    }




	SDL_Flip(ecran);//mise a jour de l ecran

	Mix_FreeChunk(son);//Libération du son 1
 	Mix_CloseAudio(); //Fermeture de l'API

	pause();
	SDL_FreeSurface(texte);
	SDL_Quit();//arreter SDL

	return EXIT_SUCCESS;
}

void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}

