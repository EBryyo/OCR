#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>
#include <err.h>


void save_texture(const char* file_name, SDL_Renderer* renderer, SDL_Texture* texture) {
    SDL_Texture* target = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, texture);
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
    IMG_SavePNG(surface, "return.png");
    SDL_FreeSurface(surface);
    SDL_SetRenderTarget(renderer, target);
}

void draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
	SDL_RenderCopy(renderer,texture,NULL,NULL);
 	SDL_RenderPresent(renderer);
}



int main(int argc, char** argv)
{

    // Checks the number of arguments.
 	if (argc != 3){
            errx(EXIT_FAILURE, "Usage: image-file and angle");}

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
         errx(EXIT_FAILURE, "%s", SDL_GetError());
     // - Create a window.
     SDL_Window* window = SDL_CreateWindow
	("Dynamic Fractal Canopy"    , 0, 0, 0,0, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
     if (window == NULL)
         errx(EXIT_FAILURE, "%s", SDL_GetError());

     // - Create a renderer.
     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
     if (renderer == NULL)
     errx(EXIT_FAILURE, "%s", SDL_GetError());
	float  angle = (float)*argv[2]; 
    
     SDL_Surface* a = load_image(argv[1]);
    
     SDL_Texture * b = SDL_CreateTextureFromSurface(renderer,a);
    
    
     SDL_RenderCopyEx(renderer, b, NULL, NULL, 50, NULL, SDL_FLIP_HORIZONTAL);
	save_texture(argv[1],renderer,b);



     SDL_FreeSurface(a);
     // - Destroy the objects.
     SDL_DestroyTexture(b);
     SDL_DestroyRenderer(renderer);
     SDL_DestroyWindow(window);
     SDL_Quit();
     return EXIT_SUCCESS;

}
