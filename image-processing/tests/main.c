#include <stdio.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


Uint32 f(Uint32 c, double n)
{
    if(c <= 255 / 2)
        return (Uint32)( (255/2) * SDL_pow((double) 2 * c / 255, n));
    else
        return 255 - f(255 - c, n);
}


Uint32 pixelGray(Uint32 pixel_color, SDL_PixelFormat* format)
{
    Uint8 r, g, b;
    SDL_GetRGB(pixel_color, format, &r, &g, &b);
    Uint8 average = 0.3*r + 0.59*g + 0.11*b;
    return SDL_MapRGB(format, average,average,average);
}
//Grayscale picture;
void Grayscale(SDL_Surface* surface)
{
    SDL_LockSurface(surface);
    Uint32* pixels = surface->pixels;
    int len = surface->w * surface->h;
    SDL_PixelFormat* format = surface->format;

    for(size_t i=0; i<len; i++)
    {
	pixels[i] = pixelGray(pixels[i], format);
	pixels[i] = f(pixels[i], 2);
    }

    SDL_UnlockSurface(surface);
}

//Save picture to png format;
void SaveImage(SDL_Surface* surface, const char *filename)
{
    IMG_SavePNG(surface, filename);
}


int main(int argc, char** argv)
{
    if (argc != 2)
	errx(EXIT_FAILURE, "Usage: ./main image-path");
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    SDL_Surface* originalImage = IMG_Load(argv[1]);
    if (originalImage == NULL)
	errx(EXIT_FAILURE, "%s", SDL_GetError());
    
    SDL_Surface* image = SDL_ConvertSurfaceFormat(originalImage, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(originalImage);

    printf("%s", "Coucouu\n");
    printf("La width est : %d\n",image->w );
    Grayscale(image);
    SaveImage(image, "test.png");


    return EXIT_SUCCESS;
}

