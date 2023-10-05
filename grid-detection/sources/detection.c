#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Surface* load_image(const char* path)
{
	SDL_Surface* grid = IMG_Load(path);
	SDL_Surface* grid_convert = 
	SDL_ConvertSurfaceFormat(grid,SDL_PIXELFORMAT_RGB888,0);
	SDL_FreeSurface(grid);
	return grid_convert;
}

int main(int argc, char** argv)
{
	if (argc != 2)
            errx(EXIT_FAILURE, "Usage: image-file");

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
            errx(EXIT_FAILURE, "%s", SDL_GetError());

        SDL_Window* window = SDL_CreateWindow("Dynamic Fractal Canopy", 0, 0, 640, 400,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (window == NULL)
            errx(EXIT_FAILURE, "%s", SDL_GetError());

        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL)
            errx(EXIT_FAILURE, "%s", SDL_GetError());

        SDL_Surface* s = load_image(argv[1]);
        if (s == NULL)
	    errx(EXIT_FAILURE, "%s", SDL_GetError());

        SDL_SetWindowSize(window,s->w,s->h);

	
	return 0;
}
