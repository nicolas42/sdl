// g++ sobel_edge_detection.cpp -framework SDL2 -ISDL2 -fsanitize=address && ./a.out


#include <stdio.h>

#include "SDL.h"
// #include "SDL_image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#include <stdint.h>
typedef uint8_t     u8;
typedef int8_t      s8;
typedef uint16_t    u16;
typedef int16_t     s16;
typedef uint32_t    u32;
typedef int32_t     s32;
typedef uint64_t    u64;
typedef int64_t     s64;
typedef float       f32;
typedef double      f64;


void sobel_edge_detection(u8* original_image, int width, int height, u8** edge_image_arg)
{
    // make a greyscale image of floats which is centered around zero.
    double *grey_image_floats = (double*)calloc(height * width, sizeof(double));
    for (int j=0; j<height; j++ ){
        for (int i=0; i<width; i++ ){
            int pos = j*width*4 + i*4;
            char r = original_image[pos+0];
            char g = original_image[pos+1];
            char b = original_image[pos+2];
            char a = original_image[pos+3];

            char v = 0.212671f * r + 0.715160f * g + 0.072169f * b;

            grey_image_floats[j*width+i] = (double)((v-127.)); // "centered" around zero

        }
    }

    // // actually center around zero by subtracting average from each value.
    // double average_color = -1;
    // double sum_of_colors = -1;
    // for (int j=0; j<height; j++ ){
    //     for (int i=0; i<width; i++ ){
    //         int pos = j*width + i;
    //         // printf("%f ", grey_image_floats[j*width+i]);
    //         sum_of_colors += grey_image_floats[j*width+i];
    //     }
    // }
    // average_color = sum_of_colors / (width*height);
    // printf("average color: %f\n", average_color);

    // for (int j=0; j<height; j++ ){
    //     for (int i=0; i<width; i++ ){
    //         grey_image_floats[j*width+i] -= average_color;
    //     }
    // }

    // Apply x and y sobel filters
    double *edge_image_floats = (double*)calloc(height * width, sizeof(double));
    for (int j=1; j<height-1; j++ ){
        for (int i=1; i<width-1; i++ ){
            int pos = j*width + i;
            double x = 
            -1 * grey_image_floats[ pos-width - 1 ]    
            +1 * grey_image_floats[ pos-width + 1 ]
            -2 * grey_image_floats[ pos - 1 ]            
            +2 * grey_image_floats[ pos + 1 ]
            -1 * grey_image_floats[ pos+width - 1 ]    
            +1 * grey_image_floats[ pos+width + 1 ];

            double y = 
            -1 * grey_image_floats[ pos-width - 1 ]    
            -2 * grey_image_floats[ pos-width ]
            -1 * grey_image_floats[ pos-width + 1 ]            
            +1 * grey_image_floats[ pos+width - 1 ]    
            +2 * grey_image_floats[ pos+width ]
            +1 * grey_image_floats[ pos+width + 1 ];            

            // x /= 9.;
            // y /= 9.;
            
            edge_image_floats[pos] = (double)sqrt( x*x + y*y );
        }
    }


    double minimum_value = edge_image_floats[0];
    double maximum_value = edge_image_floats[0];
    for (int j=1; j<height-1; j++ ){
        for (int i=1; i<width-1; i++ ){
            int pos = j*width + i;
            if ( edge_image_floats[pos] < minimum_value ) minimum_value = edge_image_floats[pos];
            if ( edge_image_floats[pos] > maximum_value ) maximum_value = edge_image_floats[pos];
        }
    }
    // printf("min %f max %f\n", minimum_value, maximum_value);


    // Convert back to a regular image
    // u8 *edge_image = (u8*)calloc(height * width * 4, sizeof(u8));
    u8* edge_image = *edge_image_arg;
    for (int j=1; j<height-1; j++ ){
        for (int i=1; i<width-1; i++ ){
            int pos = j*width*4 + i*4;
 
            // Rescale floats to fill color bytes
            // min value goes to zero
            // max value goes to 255
            // y = (max-min)*(x - min)
            u8 v = (u8)( (edge_image_floats[j*width+i] - minimum_value) / (maximum_value-minimum_value) * 255. );

            edge_image[pos+0] = v;
            edge_image[pos+1] = v;
            edge_image[pos+2] = v;
            edge_image[pos+3] = 255;
        }
    }


    free(grey_image_floats);
    free(edge_image_floats);

    // edge_image_arg = &edge_image;
}

int main( int argc, char* args[] )
{

    // This example shows how to create a SDL_Surface* with the data loaded
    // from an image file with stb_image.h (https://github.com/nothings/stb/)

    // the color format you request stb_image to output,
    // use STBI_rgb if you don't want/need the alpha channel
    int req_format = STBI_rgb_alpha;
    int width, height, orig_format;
    u8* original_image = stbi_load("../data/Valve_original.png", &width, &height, &orig_format, req_format);
    if (original_image == NULL) {
        SDL_Log("Loading image failed: %s", stbi_failure_reason());
        exit(1);
    }

    u8 *edge_image = (u8*)calloc(height * width * 4, sizeof(u8));
    sobel_edge_detection(original_image, width, height, &edge_image);

    u8 *images[2];
    int image_index = 0;
    images[0] = original_image;
    images[1] = edge_image;



    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN );
    
    SDL_Renderer* window_renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    SDL_Texture* texture = SDL_CreateTexture( window_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height );

    
    SDL_UpdateTexture( texture, NULL, images[image_index], width * 4 );
    SDL_SetRenderDrawColor( window_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
    SDL_RenderClear( window_renderer );
    SDL_RenderCopy( window_renderer, texture, NULL, NULL );
    SDL_RenderPresent( window_renderer );

    SDL_Event event;
    bool running = true;
    while ( running )
    {
        SDL_WaitEvent( &event );
        if ( event.type == SDL_QUIT ) running = false;
        if ( event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN ) {
            printf("woo keydown or mouse button\n");
            if ( image_index == 0 ) image_index = 1; else image_index = 0;

            SDL_UpdateTexture( texture, NULL, images[image_index], width * 4 );
            SDL_SetRenderDrawColor( window_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
            SDL_RenderClear( window_renderer );
            SDL_RenderCopy( window_renderer, texture, NULL, NULL );
            SDL_RenderPresent( window_renderer );
        }
    }


    SDL_Quit();
    return 0;
}


