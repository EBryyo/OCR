#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

SDL_Surface* load_image(const char* path)
{
	SDL_Surface* grid = IMG_Load(path);
	SDL_Surface* grid_convert = 
	SDL_ConvertSurfaceFormat(grid,SDL_PIXELFORMAT_RGBA888,0);
	SDL_FreeSurface(grid);
	return grid_convert;
}

int longueur_case(SDL_Surface* grid_convert)
{
	int x = 0;
	Uint32* pixels = grid_convert->pixels;
	int len = grid_convert->w * grid_convert->h;
	SDL_PixelFormat* format = grid_convert->format;
	SDL_LockSurface(grid_convert);
	Uint8* r, g, b;
	SDL_GetRGB(pixels[x],format,&r,&g,&b);
	int y = grid_convert->w;
	Uint8* rsub, gsub, bsub;
	rsub = r;
	gsub = g;
	bsub = b;
	while (rsub<200 || gsub<200 || bsub<200)
	{
		x+=1;
		y+=y;
		SDL_GetRGB(pixels[x],format,%rsub,&gsub,&bsub);
	}
	int longcase = x;
	while (rsub>100 || gsub>100 || bsub>100)
	{
		longcase+=1;
		SDL_GetRGB(pixels[longcase+y],format,%rsub,%gsub,%bsub);
	}
	while (rsub>200 || gsub<200 ||bsub<200)
	{
		longcase+=1;
		SDL_GetRGB(pixels[longcase+y],format,%rsub,%gsub,%bsub);
	}
	return longcase;
}
