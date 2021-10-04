// How to make the thing
//
// install SDL and SDL_image with a package manager or from https://libsdl.org/download-2.0.php
//
// run something like this
// 
// macos:
// 	g++ -ISDL2 -framework SDL2 -framework SDL2_image -std=c++11 show_images.cpp 

// linux:
// 	g++ -ISDL2 -lSDL2 -lSDL2_image -std=c++11 show_images.cpp



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include "dirent.h"
// #include <dirent.h> /* "readdir" etc. are defined here. */
#include <limits.h> /* limits.h defines "PATH_MAX". */

#include <iostream>
#include <string>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"
// #include "list_dir.h"

void list_dir (const char * dir_name, std::vector<std::string> *output)
{
    /* this function is from lemoda.net */

    // std::vector<std::string> output;
    std::string buff = "";

    DIR * d;

    /* Open the directory specified by "dir_name". */

    d = opendir (dir_name);

    /* Check it was opened. */
    if (! d) {
        fprintf (stderr, "Cannot open directory '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
    while (1) {
        struct dirent * entry;
        const char * d_name;

        /* "Readdir" gets subsequent entries from "d". */
        entry = readdir (d);
        if (! entry) {
            /* There are no more entries in this directory, so break
               out of the while loop. */
            break;
        }
        d_name = entry->d_name;
        /* Print the name of the file and directory. */
	// printf ("%s/%s\n", dir_name, d_name);

    buff = "";
    buff += dir_name;
    buff += "/";
    buff += d_name;
    // buff += "\n";
    output->push_back(buff);

#if 0
	/* If you don't want to print the directories, use the
	   following line: */

        if (! (entry->d_type & DT_DIR)) {
	    // printf ("%s/%s\n", dir_name, d_name);

        buff = "";
        buff += dir_name;
        buff += "/";
        buff += d_name;
        // buff += "\n";
        output->push_back(buff);
	}

#endif /* 0 */


        if (entry->d_type & DT_DIR) {

            /* Check that the directory is not "d" or d's parent. */
            
            if (strcmp (d_name, "..") != 0 &&
                strcmp (d_name, ".") != 0) {
                int path_length;
                char path[PATH_MAX];
 
                path_length = snprintf (path, PATH_MAX,
                                        "%s/%s", dir_name, d_name);
                // printf ("%s\n", path);

                buff = "";
                buff += path;
                // buff += "\n";
                output->push_back(buff);


                if (path_length >= PATH_MAX) {
                    fprintf (stderr, "Path length has got too long.\n");
                    exit (EXIT_FAILURE);
                }
                /* Recursively call "list_dir" with the new path. */
                list_dir (path,output);
            }
	}
    }
    /* After going through all the entries, close the directory. */
    if (closedir (d)) {
        fprintf (stderr, "Could not close '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }


}

// int list_dir_main (int argc, char **argv)
// {
//     // char *dir = argv[1]; // "/Users/nick/Downloads";
//     const char *dir = "/Users/nick/Downloads";

	// std::vector<std::string> files;
	// list_dir("/Users/nick/Downloads", &files);
	// for (auto f : files) {
	// 	const char *extension = f.substr(f.find_last_of(".") + 1).c_str();
	// 	if (strcmp(extension, "jpg")==0) std::cout << f << std::endl;
	// 	// std::cout << extension << std::endl;
	// 	// std::cout << f << std::endl;
	// }
// }



double get_scaler_to_fit( SDL_Surface* a, SDL_Surface* b )
{
    // find the scaler required to fit the a inside the b
    // multiply the dimensions of a by the scaler get get the desired size


    // An aspect ratio is a width divided by a height e.g. 800/600 = 1.33
    // if an aspect ratio is higher than another then it is more of a "panorama" type a than the other one.
    //
    // if an a's aspect ratio is higher than the windows then we set the width of the a to the width of the b
    // then we scale the images height accordingly.  If the 
    
    double image_aspect_ratio = ((double)a->w) / ((double)a->h);
    double window_aspect_ratio = ((double)b->w) / ((double)b->h);
    double scaler = 1;

    if ( image_aspect_ratio > window_aspect_ratio ) {
        // fit width
        scaler = ((double)b->w) / ((double)a->w);
    } else {
        // fit height
        scaler = ((double)b->h) / ((double)a->h);
    }

    // printf("%f %f %f \n", image_aspect_ratio, window_aspect_ratio, scaler);
    return scaler;
}


int main( int argc, char* argv[] )
{
    int window_width = 400;
    int window_height = 800;

	const char *dir;
	if (argc==2){
		dir = argv[1];
	} else {
        printf("show_images <dir>\n");
        return -1;
	}

	const char *desired_extensions[] = {"jpg", "png", "bmp", "jpeg"};
	std::vector<std::string> all_filenames;
	list_dir(dir, &all_filenames);

	std::vector<std::string> filenames;
	for (auto f : all_filenames) {
		const char *extension = f.substr(f.find_last_of(".") + 1).c_str();
		for (auto desired_extension : desired_extensions ){
			if (strcmp(extension, desired_extension)==0) {
				filenames.push_back(f);
				// std::cout << f << std::endl;
				break;
			}
		}
	}

	for (auto i:filenames) std::cout << i << std::endl;
	int filenames_index = 0;
	const int filenames_length = filenames.size();


	SDL_Init( SDL_INIT_VIDEO );
	IMG_Init( IMG_INIT_PNG & IMG_INIT_JPG );

	SDL_Window* window;
	SDL_Surface* window_surface;

	window = SDL_CreateWindow( "Press any key :)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE ); // SDL_WINDOW_FULLSCREEN_DESKTOP ); // 

	// SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

	window_surface = SDL_GetWindowSurface( window );


	bool gui_needs_updating = false;
	bool running = true;
	bool is_fullscreen = false;


    while (running)
    {
		SDL_Event event;
        SDL_WaitEvent(&event);
 
		switch (event.type){

		case SDL_QUIT:
			running = false;
			break;

        case SDL_WINDOWEVENT:
            printf("window event\n");

            switch ( event.window.event ){
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                // SDL_Log("Window %d resized to %dx%d",
                //     event.window.windowID, event.window.data1,
                //     event.window.data2);
                // window_width = event.window.data1;
                // window_height = event.window.data2;
                SDL_FreeSurface(window_surface);
                window_surface = SDL_GetWindowSurface( window );
                printf("%d %d\n", window_surface->w, window_surface->h );
                break;


            }
            break;

		case SDL_KEYDOWN:

			switch (event.key.keysym.sym){

			case SDLK_RIGHT:
				filenames_index += 1;
				if ( filenames_index >= filenames_length ) filenames_index = 0;
				gui_needs_updating = true;
				break;

			case SDLK_LEFT:
				filenames_index += -1;
				if ( filenames_index < 0 ) filenames_index = filenames_length-1;
				gui_needs_updating = true;
				break;

			case SDLK_f:
				printf("Hello\n");
				if (is_fullscreen) {
					SDL_SetWindowFullscreen(window, 0);
				} else {
					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
				}
				is_fullscreen = !is_fullscreen;
				
				break;

			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			filenames_index += -1;
			if ( filenames_index < 0 ) filenames_index = filenames_length-1;
			gui_needs_updating = true;
			break;

		}

		if (gui_needs_updating) {

            SDL_Surface* image;
			SDL_Surface *optimised_image_surface;

			SDL_SetWindowTitle(window, filenames[filenames_index].c_str());
			image = IMG_Load( filenames[filenames_index].c_str() );
			optimised_image_surface = SDL_ConvertSurface( image, window_surface->format, 0 );

			SDL_FillRect(window_surface, NULL, SDL_MapRGB(window_surface->format, 0, 0, 0));

            double scaler = get_scaler_to_fit( image, window_surface );

            SDL_Rect new_size = { .x = 0, .y = 0, .w = (int)(scaler * image->w), .h = (int)(scaler * image->h) };
			SDL_BlitScaled( optimised_image_surface, NULL, window_surface, &new_size );

			SDL_UpdateWindowSurface( window );
			gui_needs_updating = false;
            
            // SDL_FreeSurface(image);
            // SDL_FreeSurface(optimised_image_surface);
		}

    }


	SDL_FreeSurface( window_surface );
	// SDL_FreeSurface( image );
	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}
