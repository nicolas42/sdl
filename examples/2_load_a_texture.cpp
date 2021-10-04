/*
clang++ load_a_texture.cpp -framework SDL2 -framework SDL2_image
*/


#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <stdio.h>
#include <string>

int main( int argc, char** args )
{

    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = NULL;
    int image_flags = 0;

    int window_height = 800;
    int window_width  = 800;
    window = SDL_CreateWindow( "title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN );
    
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    SDL_SetRenderDrawColor ( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    image_flags = IMG_INIT_PNG;

    char filename[] = "texture.png";
    surface = IMG_Load( filename );
    texture = SDL_CreateTextureFromSurface( renderer, surface );

    int running = 1;
    SDL_Event event;

    while (running) 
    {
        while ( SDL_PollEvent(&event) != 0 ) { if ( event.type == SDL_QUIT ) running = 0; }

        // clear screen, render texture onto the screen, update screen
        SDL_RenderClear( renderer );
        SDL_RenderCopy ( renderer, texture, NULL, NULL );
        SDL_RenderPresent ( renderer );
    }
    
    

    

	return 0;
}
