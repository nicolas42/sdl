/*
g++ test.cpp -framework SDL2

Get window window_surface then get the pixels array from that and then draw stuff on it.
*/

#include <SDL2/SDL.h>        
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void draw_mandelbrot_in_black_and_white(int w, int h, int c, char **ret_image)
{
    double xcenter = 0;
    double ycenter = 0;
    double width = 4;
    double height = 4;

    char *image = *ret_image;
    const unsigned char black[4] = {0, 0, 0, 255};
    const unsigned char white[4] = {255, 255, 255, 255};
    
    for (int y = 0; y < h ; y += 1) {
        for (int x = 0; x < w; x += 1) {

            double zx, zxtmp, zy, cx, cy;
            int is_in_set, i;
            const int max_iterations = 40;

            // image is flipped vertically
            cx = x * (width / w) - (xcenter + width/2);
            cy = y * (height / h) - (ycenter + height/2);
            zx = 0;
            zy = 0;
            is_in_set = 1;

            for(i = 1; i <= max_iterations; i += 1){
                zxtmp = zx * zx - zy * zy + cx;
                zy = 2 * zx * zy + cy;
                zx = zxtmp;
                if(zx * zx + zy * zy > 4){
                    is_in_set = 0;
                    break;
                }
            }
            
            if (is_in_set) {
				image[y*w*c + x*c + 0] = (char)black[0];
                image[y*w*c + x*c + 1] = (char)black[1];
                image[y*w*c + x*c + 2] = (char)black[2];
                image[y*w*c + x*c + 3] = 255;
            } else {
				image[y*w*c + x*c + 0] = white[0] * i / max_iterations;
                image[y*w*c + x*c + 1] = white[1] * i / max_iterations;
                image[y*w*c + x*c + 2] = white[2] * i / max_iterations;
                image[y*w*c + x*c + 3] = 255;
			}
        }
    }
    *ret_image = image;  
}




int main(int argc, char ** argv)
{
    int w = 800, h = 800, c = 4;
    // unsigned char *stbi_loaded_image = stbi_load("texture.png", &w, &h, &c, 4);
    // for (int i=0; i<w*h*c; i++) window_surface_pixels[i] = stbi_loaded_image[i];

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("SDL2 Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0);
    SDL_Surface *window_surface = SDL_GetWindowSurface(window);


    SDL_LockSurface(window_surface);
    char *window_surface_pixels = (char*)(window_surface->pixels);
    draw_mandelbrot_in_black_and_white(w,h,c, &window_surface_pixels);
    SDL_UnlockSurface(window_surface);
    SDL_UpdateWindowSurface(window);


    bool running = true;
    SDL_Event event;
    while (running)
    {
        while ( SDL_PollEvent( &event ) )
        {
            if ( event.type == SDL_QUIT )
            {
                running = false;
                break;
            }
        }
    }    
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}

