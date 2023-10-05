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
	while (r==0)
	{
		x+=1;
		y+=y;
		SDL_GetRGB(pixels[x],format,%r,&g,&b);
	}
	int longcase = x;
	while (r==255)
	{
		longcase+=1;
		SDL_GetRGB(pixels[longcase+y],format,%r,%g,%b);
	}
	while (r==0)
	{
		longcase+=1;
		SDL_GetRGB(pixels[longcase+y],format,%r,%g,%b);
	}
	return longcase;
}

Uint32* decoupe_number(SDL_Surface* grid_convert, int x, int y, int longcase)
{
	//longueur case avec des trucs vides
	Uint32* bloc[longcase*longcase];

	//format des pixels
	SDL_PixelFormat* format = grid_convert->format;
	
	//hauteur
	for (int j = 0;j<=longcase;j++)
	{
		//longueur
		for (int i = 0;i<=longcase;i++)
		{
			bloc[j*longcase+i] = SDL_MapRGB(format,&r,&g,&b);
		}
	}
	return bloc;
}

Uint32** decoupe_grid(SDL_Surface* grid_convert, int longcase)
{
	Uint32** res[longcase][longcase];
	for (size_t j = 0;j!=9;j++)
	{
		for (size_t i = 0;i!=9;i++)
		{
			res[i] = decoupe_number(grid_convert,
				i*longcase,j*longcase,longcase);
		}
	}
	return res;
}




















