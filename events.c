#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "includes.h"

void events_Loop(void (*main_loop)()) {

    bool quit = false;
    SDL_Event event;

    while (!quit) {

        /*
        printf("wait for event...\n");
        
        SDL_WaitEvent(&event);

        printf("wait ended...\n");

        if (event.type == SDL_QUIT) {
            printf("quitting...\n");
            quit = true;
        }
        */
        
        while( SDL_PollEvent(&event) != 0) {
            // printf("polling event...\n");
            // User requests quit
            if(event.type == SDL_QUIT) {
                // printf("quitting...\n");
                quit = true;
			}
            
		}

        // printf("wait ended...\n");

        // main loop
        main_loop();

        //SDL_Delay(500);

    }
    
    return;
}