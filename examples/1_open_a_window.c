// macos
// gcc 1_open_a_window.c -framework SDL2

// linux
// gcc 1_open_a_window.c -lSDL2

#include <SDL2/SDL.h>        
 
int main(int argc, char ** argv)
{
    int quit = 0;
    SDL_Event event;
 
    SDL_Init(SDL_INIT_VIDEO);
 
    SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
 
    while (!quit)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = 1;
            break;
        }
    }
 
    SDL_Quit();
 
    return 0;
}