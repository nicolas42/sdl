#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"


int open_a_window( int argc, char* args[] )
{
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    SDL_Init( SDL_INIT_VIDEO );
    SDL_Window *window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    SDL_Surface *surface = SDL_GetWindowSurface( window );
    SDL_FillRect( surface, NULL, SDL_MapRGB( surface->format, 0xFF, 0x00, 0x00 ) );
    SDL_UpdateWindowSurface( window );

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

// Load an image an blit it to the screen
// ---------------------------------------
// surfaces are software rendered images
// blitting is copying an image to another image
// rendering is typically done to a backbuffer which needs to be swapped out with the front buffer to actually show something


// What blitting does is take a source surface and stamps a copy of it onto the destination surface. The first argument of SDL_BlitSurface is the source image. The third argument is the destination. We'll worry about the 2nd and 4th arguments in future tutorials.

// After drawing everything on the screen that we want to show for this frame we have to update the screen using SDL_UpdateWindowSurface. See when you draw to the screen, you are not typically drawing to the image on the screen you see. By default, most rendering systems out there are double buffered. These two buffers are the front and back buffer.

// When you make draw calls like SDL_BlitSurface, you render to the back buffer. What you see on the screen is the front buffer. The reason we do this is because most frames require drawing multiple objects to the screen. If we only had a front buffer, we would be able to see the frame as things are being drawn to it which means we would see unfinished frames. So what we do is draw everything to the back buffer first and once we're done we swap the back and front buffer so now the user can see the finished frame.

// This also means that you don't call SDL_UpdateWindowSurface after every blit, only after all the blits for the current frame are done.


int load_a_bmp_and_blit_it_to_the_screen( int argc, char* args[] )
{
    SDL_Surface *image_surface = SDL_LoadBMP( "../data/lenna.bmp" );

    SDL_Init( SDL_INIT_VIDEO );
    SDL_Window *window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, image_surface->w, image_surface->h, SDL_WINDOW_SHOWN );
    SDL_Surface *surface = SDL_GetWindowSurface( window );

    SDL_BlitSurface( image_surface, NULL, surface, NULL );
    SDL_UpdateWindowSurface( window );

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




// Respond to left and right arrow events 

int respond_to_left_and_right_keyboard_events( int argc, char* args[] )
{

    SDL_Init( SDL_INIT_VIDEO );
    SDL_Window *window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN );
    SDL_Surface *surface = SDL_GetWindowSurface( window );

    SDL_Surface *surfaces[2];
    surfaces[0] = SDL_LoadBMP( "../data/lenna.bmp" );
    surfaces[1] = SDL_LoadBMP( "../data/smiley.bmp" );
    int surface_index = 1;

    SDL_Event event;
    int running = 1;
    int gotta_update = 1;
    while ( running ) {
        SDL_WaitEvent(&event);
        if ( event.type == SDL_QUIT ) running = 0;
        if ( event.type == SDL_KEYDOWN ) {
            if ( event.key.keysym.sym == SDLK_LEFT ) 
            {
                printf("omg left\n");
                surface_index = 0; 
                gotta_update = 1;
            } 
            if ( event.key.keysym.sym == SDLK_RIGHT )
            {
                printf("omg right\n");
                surface_index = 1;
                gotta_update = 1;
            }
        }

        if (gotta_update) {
            SDL_FillRect( surface, NULL, SDL_MapRGB( surface->format, 0x00, 0x00, 0x00 ) );
            SDL_BlitSurface( surfaces[surface_index], NULL, surface, NULL );
            SDL_UpdateWindowSurface( window );
            gotta_update = 0;
        }
    }


    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;
}


// Scale an image and optimise it for faster blitting
// --------------------------------------------------------------

// You can optimise an image to have the same format as the underlying surface that it's going to render to
// with SDL_ConvertSurface(a, surface->format, 0); omgomgomg

// You can also scale surfaces when you blit them using this call
// SDL_BlitScaled( images[image_index], NULL, window, &window_size );
// window_size is an SDL_Rect which is what you might imagine.
// a rectangle has x,y,w, and h parameters. yay.  it describes a rectangular area on the screen 
// or I suppose any rectangle that you might be interested in.


int scale_an_image_and_optimise_it_for_faster_blitting( int argc, char* args[] )
{
    const int WINDOW_WIDTH  = 800;
    const int WINDOW_HEIGHT = 800;
    
    SDL_Init( SDL_INIT_VIDEO );
    SDL_Window *window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
    SDL_Surface *window_surface = SDL_GetWindowSurface( window );

    SDL_Surface *image_surfaces[2];
    int image_index = 0;

    char filenames[2][20] = { "../data/lenna.bmp", "../data/smiley.bmp" };

    // load images
    if (0) 
    {
        image_surfaces[0] = SDL_LoadBMP( filenames[0] );
        image_surfaces[1] = SDL_LoadBMP( filenames[1] );
    } 
    else 
    {
        SDL_Surface *tmp;

        tmp = SDL_LoadBMP( filenames[0] );
        image_surfaces[0] = SDL_ConvertSurface( tmp, window_surface->format, 0 );
        SDL_FreeSurface(tmp);

        tmp = SDL_LoadBMP( filenames[1] );
        image_surfaces[1] = SDL_ConvertSurface( tmp, window_surface->format, 0 );
        SDL_FreeSurface(tmp);
    }


    SDL_Event event;
    int running = 1;
    int gotta_update = 1;
    while ( running ) {
        SDL_WaitEvent(&event);

        if ( event.type == SDL_QUIT ) running = 0;

        if ( event.type == SDL_KEYDOWN ) {
            if ( event.key.keysym.sym == SDLK_LEFT ) 
            {
                printf("omg left\n");
                image_index = 0; 
                gotta_update = 1;
            } 
            if ( event.key.keysym.sym == SDLK_RIGHT )
            {
                printf("omg right\n");
                image_index = 1;
                gotta_update = 1;
            }
        }

        if (gotta_update) {
            SDL_FillRect( window_surface, NULL, SDL_MapRGB( window_surface->format, 0x00, 0x00, 0x00 ) );
            SDL_Rect window_size = { .x = 0, .y = 0, .w = WINDOW_WIDTH, .h = WINDOW_HEIGHT };
            SDL_BlitScaled( image_surfaces[image_index], NULL, window_surface, &window_size );
            SDL_BlitSurface( image_surfaces[image_index], NULL, window_surface, 0 );
            SDL_UpdateWindowSurface( window );
            gotta_update = 0;
        }
    }


    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;
}


int lets_load_a_png( int argc, char* args[] )
{
    const int WINDOW_WIDTH  = 800;
    const int WINDOW_HEIGHT = 800;
    
    SDL_Init( SDL_INIT_VIDEO );
    SDL_Window *window_object = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
    SDL_Surface *window = SDL_GetWindowSurface( window_object );

    IMG_Init( IMG_INIT_PNG );
    SDL_Surface* image = IMG_Load( "nyan_cat.png" ); 

	

    SDL_Event event;
    int running = 1;
    while ( running ) {
        SDL_WaitEvent(&event);
        if ( event.type == SDL_QUIT ) running = 0;

        SDL_FillRect( window, NULL, SDL_MapRGB( window->format, 0x00, 0x00, 0x00 ) );
        SDL_Rect window_size = { .x = 0, .y = 0, .w = WINDOW_WIDTH, .h = WINDOW_HEIGHT };
        SDL_BlitScaled( image, NULL, window, &window_size );
        SDL_UpdateWindowSurface( window_object );

    }


    SDL_DestroyWindow( window_object );
    SDL_Quit();
    return 0;
}




// Textures are hardware rendered images

// There's a bug where if I call SDL_GetWindowSurface on the window then
// it screws up CreateTextureFromSurface


int use_textures_to_render_an_image( int argc, char* args[] )
{
    const int WINDOW_WIDTH  = 800;
    const int WINDOW_HEIGHT = 800;
    
    SDL_Init( SDL_INIT_VIDEO );
    IMG_Init( IMG_INIT_PNG );

    SDL_Window *window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
    // SDL_Surface *surface = SDL_GetWindowSurface( window );
    SDL_Renderer *window_renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    SDL_SetRenderDrawColor( window_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    SDL_Surface* tmp = IMG_Load( "lena.png" ); 
	SDL_Texture *image = SDL_CreateTextureFromSurface( window_renderer, tmp );
    if (image == NULL) printf("shit shit fucking guard dogs!\n");
    SDL_FreeSurface(tmp);


    SDL_Event event;
    int running = 1;
    while ( running ) {
        SDL_WaitEvent(&event);
        if ( event.type == SDL_QUIT ) running = 0;

        SDL_RenderClear( window_renderer );
        SDL_RenderCopy( window_renderer, image, NULL, NULL );
        SDL_RenderPresent( window_renderer );
    }


    SDL_DestroyWindow( window );
    SDL_DestroyTexture( image );
    SDL_DestroyRenderer( window_renderer );
    IMG_Quit();
    SDL_Quit();
    return 0;
}



#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

// from https://stackoverflow.com/questions/33304351/sdl2-fast-pixel-manipulation
// clang++ -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_net -framework SDL2_ttf -Wno-c++11-extensions -ISDL2 render_random_pixels.cpp
int render_random_pixels( int argc, char** argv )
{
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window* window = SDL_CreateWindow
        (
        "SDL2",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        600, 600,
        SDL_WINDOW_SHOWN
        );

    SDL_Renderer* renderer = SDL_CreateRenderer
        (
        window,
        -1,
        SDL_RENDERER_ACCELERATED
        );

    SDL_RendererInfo info;
    SDL_GetRendererInfo( renderer, &info );
    std::cout << "Renderer name: " << info.name << std::endl;
    std::cout << "Texture formats: " << std::endl;
    for( Uint32 i = 0; i < info.num_texture_formats; i++ )
    {
        std::cout << SDL_GetPixelFormatName( info.texture_formats[i] ) << std::endl;
    }

    const unsigned int texWidth = 1024;
    const unsigned int texHeight = 1024;
    SDL_Texture* texture = SDL_CreateTexture
        (
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        texWidth, texHeight
        );

    std::vector< unsigned char > pixels( texWidth * texHeight * 4, 0 );

    SDL_Event event;
    bool running = true;
    bool useLocktexture = false;
    
    unsigned int frames = 0;
    Uint64 start = SDL_GetPerformanceCounter();

    while( running )
    {

        SDL_SetRenderDrawColor( renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
        SDL_RenderClear( renderer );

        while( SDL_PollEvent( &event ) )
        {
            if( ( SDL_QUIT == event.type ) ||
                ( SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode ) )
            {
                running = false;
                break;
            }
            if( SDL_KEYDOWN == event.type && SDL_SCANCODE_L == event.key.keysym.scancode )
            {
                useLocktexture = !useLocktexture;
                std::cout << "Using " << ( useLocktexture ? "SDL_LockTexture() + memcpy()" : "SDL_UpdateTexture()" ) << std::endl;
            }
        }
        
        // splat down some random pixels
        for( unsigned int i = 0; i < 1000; i++ )
        {
            const unsigned int x = rand() % texWidth;
            const unsigned int y = rand() % texHeight;

            const unsigned int offset = ( texWidth * 4 * y ) + x * 4;
            pixels[ offset + 0 ] = rand() % 256;        // b
            pixels[ offset + 1 ] = rand() % 256;        // g
            pixels[ offset + 2 ] = rand() % 256;        // r
            pixels[ offset + 3 ] = SDL_ALPHA_OPAQUE;    // a
        }

        if( useLocktexture )
        {
            unsigned char* lockedPixels = nullptr;
            int pitch = 0;
            SDL_LockTexture
                (
                texture,
                NULL,
                reinterpret_cast< void** >( &lockedPixels ),
                &pitch
                );
            std::memcpy( lockedPixels, pixels.data(), pixels.size() );
            SDL_UnlockTexture( texture );
        }
        else
        {
            SDL_UpdateTexture
                (
                texture,
                NULL,
                pixels.data(),
                texWidth * 4
                );
        }

        SDL_RenderCopy( renderer, texture, NULL, NULL );
        SDL_RenderPresent( renderer );
        
        frames++;
        const Uint64 end = SDL_GetPerformanceCounter();
        const static Uint64 freq = SDL_GetPerformanceFrequency();
        const double seconds = ( end - start ) / static_cast< double >( freq );
        if( seconds > 2.0 )
        {
            std::cout
                << frames << " frames in "
                << std::setprecision(1) << std::fixed << seconds << " seconds = "
                << std::setprecision(1) << std::fixed << frames / seconds << " FPS ("
                << std::setprecision(3) << std::fixed << ( seconds * 1000.0 ) / frames << " ms/frame)"
                << std::endl;
            start = end;
            frames = 0;
        }
    }

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}


// make
// g++ lazyfoo_examples.cpp -framework SDL2 -framework SDL2_image -ISDL2 && ./a.out
// 
// SDL2_image is just needed for reading png files

int main( int argc, char* args[] )
{
    // open_a_window(argc, args);
    // load_a_bmp_and_blit_it_to_the_screen( argc, args);
    // respond_to_left_and_right_keyboard_events( argc, args);
    // lets_load_a_png( argc, args);
    // use_textures_to_render_an_image( argc, args);

    // scale_an_image_and_optimise_it_for_faster_blitting( argc, args);

    render_random_pixels(argc,args);
    return 0;
}
