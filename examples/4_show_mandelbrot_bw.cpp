/*
g++ show_mandelbrot_bw.cpp -framework SDL2

// from https://stackoverflow.com/questions/33304351/sdl2-fast-pixel-manipulation
*/

#include <SDL2/SDL.h>        
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>



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

    int texture_width = 800;
    int texture_height = 800;
    int c = 4;
    char *pixels = (char*)malloc(texture_width*texture_height*c*sizeof(char));
    draw_mandelbrot_in_black_and_white(texture_width,texture_height,c,&pixels);


    SDL_Init( SDL_INIT_EVERYTHING );
    int window_width = 800;
    int window_height = 800;
    SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN );
    
    SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    SDL_Texture* texture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, texture_width, texture_height );
    SDL_Event event;
    bool running = true;

    while ( running )
    {
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
        SDL_RenderClear( renderer );

        while ( SDL_PollEvent( &event ) )
        {
            if ( event.type == SDL_QUIT )
            {
                running = false;
                break;
            }
        }
        
        SDL_UpdateTexture( texture, NULL, pixels, texture_width * 4 );
        SDL_RenderCopy( renderer, texture, NULL, NULL );
        SDL_RenderPresent( renderer );
    }

    
    SDL_Quit();
 
    return 0;
}