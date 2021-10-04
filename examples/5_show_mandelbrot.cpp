// Call vcvarsall.bat wherever it is.  Then update the PATH environmental variable to the lib_win64 directory.
// Alternatively you could just move all of the DLL files from that directory to the same directory as your executable.
//
// @REM call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
// @REM SET PATH=%PATH%;c:\nick\sdl_cross_platform\lib_win64
//
// cl /std:c++latest /I "include" "sdl\5_show_mandelbrot.cpp" /link "lib_win64\SDL2.lib" "lib_win64\SDL2main.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS 


/*
g++ 5_show_mandelbrot.cpp -framework SDL2 && ./a.out
g++ 5_show_mandelbrot.cpp -lSDL2 && ./a.out

// from https://stackoverflow.com/questions/33304351/sdl2-fast-pixel-manipulation
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"


float hue2rgb(float p, float q, float t) {
    if (t < 0.) {
        t += 1.;
    }
    if (t > 1.) {
        t -= 1.;
    }
    if (t < 1. / 6.) {
        return p + (q - p) * 6. * t;
    }
    if (t < 1. / 2.) {
        return q;
    }
    if (t < 2. / 3.) {
        return p + (q - p) * (2. / 3. - t) * 6.;
    }
    return p;
}

void hsl2rgb(float h, float s, float l, int rgb[3]) {

    // if (h!=0.0) printf("%f %f %f\n", h,s,l);

    float r;
    float g;
    float b;

    float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    float p = 2. * l - q;
    // printf("%f %f %f\n", p,q,h);

    if (s == 0.) {
        r = 1.;
        g = 1.;
        b = 1.; // achromatic
    } else {

        r = hue2rgb(p, q, h + 1. / 3.);
        g = hue2rgb(p, q, h);
        b = hue2rgb(p, q, h - 1. / 3.);
    }

    // printf("%f %f %f\n", r,g,b);
    rgb[0] = (int)(r * 255.);
    rgb[1] = (int)(g * 255.);
    rgb[2] = (int)(b * 255.);

}
    


struct image {
    // width, height, number of channels, image data
    int w;
    int h;
    int c;
    char *data;
};


void draw_mandelbrot(struct image im, double x, double y, double zoom, double max_iterations )
{
    const unsigned char black[4] = {0, 0, 0, 255};
    // const unsigned char white[4] = {255, 255, 255, 255};

    for (double j = 0; j < im.h; j += 1) {
        for (double i = 0; i < im.w; i += 1) {

            // get math point from image point
            // image is flipped vertically. numbers go up, pixels go down. i don't care.
            double h = 4. / zoom;
            double w = 4. / zoom;

            // z = z^2 + c
            double cx = (x - w / 2) + i * (w / im.w);
            double cy = (y - h / 2) + j * (w / im.w);
            double zx = 0;
            double zy = 0;
            double in_set = 1;
            int num_iterations = 1;
            while ( num_iterations <= max_iterations ) {
                double zxtemp = zx * zx - zy * zy + cx;
                zy = 2 * zx * zy + cy;
                zx = zxtemp;
                // if length of complex vector exceeds 4 then 
                // assume the pixel is not in the set
                if (zx * zx + zy * zy > 4) {
                    in_set = 0;
                    break;
                }
                num_iterations += 1;
            }

            int pos = (j * im.w * im.c) + (i * im.c);
            if (in_set) {
                im.data[pos + 0] = black[0];
                im.data[pos + 1] = black[1];
                im.data[pos + 2] = black[2];
                im.data[pos + 3] = black[3];
            } else {

                // hue is determined by the number of iterations taken
                // double rgb = hsl_to_rgb((num_iterations % 255) / 255, 1, 0.5);
                int color[3];
                hsl2rgb((num_iterations % 255) / 255., 1., 0.5, color);
                // printf("%d %d %d\n", color[0], color[1], color[2] );

                im.data[pos + 0] = color[0];
                im.data[pos + 1] = color[1];
                im.data[pos + 2] = color[2];
                im.data[pos + 3] = 255;
            }


        }
    }
}


struct image make_image(double w, double h, double c)
{
    struct image im;
    im.w = w;
    im.h = h;
    im.c = c;
    im.data = (char*)malloc(im.w * im.h * im.c );
    return im;
}


int texture_main(int argc, char ** argv)
{
    int WINDOW_WIDTH = 800;
    int WINDOW_HEIGHT = 800;
    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_Window* window_surface = SDL_CreateWindow("title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
    SDL_Renderer* window_renderer = SDL_CreateRenderer( window_surface, -1, SDL_RENDERER_ACCELERATED );

    struct image image;
    SDL_Texture* texture;

    image = make_image(WINDOW_WIDTH, WINDOW_HEIGHT, 4); // width, height, number of channels
    draw_mandelbrot(image, -0.6999687500000003, -0.2901249999999999, 1000, 1000); // x,y,zoom,max_iterations

    texture = SDL_CreateTexture( window_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, image.w, image.h );
    SDL_SetRenderDrawColor( window_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
    SDL_UpdateTexture( texture, NULL, image.data, image.w * image.c );
    SDL_RenderClear( window_renderer );
    SDL_RenderCopy( window_renderer, texture, NULL, NULL );
    SDL_RenderPresent( window_renderer );

    SDL_Event event;
    bool running = true;
    int i = 0;
    while ( running )
    {
        SDL_WaitEvent(&event);
        if ( event.type == SDL_QUIT ) running = false;
        printf("event %d\n", i++);
    }

    SDL_DestroyTexture(texture);
    free(image.data);
    SDL_Quit();
 
    return 0;
}



int main( int argc, char* args[] )
{
    const int w  = 800;
    const int h = 800;
    const int c = 4; // # channels

    SDL_Init( SDL_INIT_VIDEO );
    SDL_Window *window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN );
    SDL_Surface *window_surface = SDL_GetWindowSurface( window );

    SDL_Surface *image_surface = SDL_CreateRGBSurface(0,w,h,32,0xff000000,0x00ff0000,0x0000ff00,0x000000ff);
    struct image image = { .w = w, .h = h, .c = c };
    image.data = (char*)(image_surface->pixels);
    
    // SDL_LockSurface(image_surface);
    draw_mandelbrot(image, -0.6999687500000003, -0.2901249999999999, 1000, 1000);
    SDL_BlitSurface( image_surface, NULL, window_surface, NULL );
    // SDL_UnlockSurface(image_surface);
    SDL_UpdateWindowSurface(window);

    SDL_Event event;
    int running = 1;
    while ( running ) {
        SDL_WaitEvent(&event);
        if ( event.type == SDL_QUIT ) running = 0;

    }


    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;
}
