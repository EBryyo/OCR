#include <stdio.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "headers/decoupe.h"
#include "headers/detection.h"

int main()//int argc, char* argv[])
{
	//if (argc !=2)
	//	errx(EXIT_FAILURE, "les parametres ca va pas du tout mon gars");

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		errx(EXIT_FAILURE,"%s",SDL_GetError());

	SDL_Window* window = SDL_CreateWindow("frame decoupe",0,0,600,600,0);
	if (window == NULL)
		errx(EXIT_FAILURE,"%s",SDL_GetError());

	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);
	if (renderer == NULL)
		errx(EXIT_FAILURE,"%s",SDL_GetError());
	
	//SDL_Surface* grid = load_image(argv[1]);
	//if (grid == NULL)
	//	errx(EXIT_FAILURE,"%s",SDL_GetError());

	//return fonction de decoupe qui renvoie array de float.

	SDL_Quit(); 
	return 0;
}
