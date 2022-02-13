#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "boundBox.h"
int boundBox(SDL_Rect Box1,SDL_Rect Box2)
{

	if(Box1.x + Box1.w < Box2.x || Box1.x > Box2.x + Box2.w ||Box1.y >Box2.y + Box2.h || Box1.y +Box1.h < Box2.y)
	{

		return 0;
	}
	else
	{
	 	return  1;

	}
}
