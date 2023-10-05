#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Surface* load_image (const char* path);

int longueur_case(SDL_Surface* grid_convert);

Uint32* decoupe_number(SDL_Surface* grid_convert, int x, int y, int longcase);

Uint32** decoupe_grid(SDL_Surface* grid_convert, int longcase);
