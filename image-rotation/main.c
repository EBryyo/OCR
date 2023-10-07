#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <err.h>

int main(int argc, char** argv)
{
    SDL_Rect dstrect;
    
    // Checks the number of arguments.
    if (argc != 3)
    {errx(EXIT_FAILURE, "Usage: image-file and angle");}
    
    // - Load the surface.
     SDL_Surface* a = IMG_Load(argv[1]);
     // Create renderer
     SDL_Renderer* renderer = SDL_CreateSoftwareRenderer(a);

     if (renderer == NULL)
     {errx(EXIT_FAILURE, "%s", SDL_GetError());}

     
     //Calculating background size
     int x = sqrt(a->h*a->h+a->w*a->w);
     double angle = atof(argv[2]);
     //Initial image texture
     SDL_Texture * b = SDL_CreateTextureFromSurface(renderer,a);
     //Create a black background to rotate the image inside
     SDL_Surface * c = SDL_CreateRGBSurface(0,x,x,32,0,0,0,0); 
     SDL_Renderer * cre = SDL_CreateSoftwareRenderer(c);
     //Calculation of image position in background
     dstrect.h = a->h;
     dstrect.w = a->w;
     dstrect.x = x/2 - ((a->w)/2);
     dstrect.y = x/2 - ((a->h)/2);
         
     //Rotating and saving rotated images
     SDL_Texture * cb = SDL_CreateTextureFromSurface(cre,a); 
     SDL_RenderCopyEx(cre,cb,NULL,&dstrect,angle,NULL,SDL_FLIP_NONE);
     IMG_SavePNG(c,"c.png");

     // - Destroy the objects.
     SDL_FreeSurface(a);
     SDL_FreeSurface(c);
     SDL_DestroyRenderer(cre);
     SDL_DestroyTexture(cb);
     SDL_DestroyTexture(b);
     SDL_DestroyRenderer(renderer);

     return EXIT_SUCCESS;

}
