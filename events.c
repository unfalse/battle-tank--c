#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "includes.h"

void events_Loop(void (*main_loop)()) {

    bool quit = false;
    SDL_Event event;

    while (!quit) {

        SDL_WaitEvent(&event);
        
        //while( SDL_PollEvent(&event) != 0) {
            // printf("polling event...\n");
            // User requests quit
            if(event.type == SDL_QUIT) {
                // printf("quitting...\n");
                quit = true;
			}
            
		//}

        // printf("wait ended...\n");

        main_loop(event);

        SDL_Delay(10);

    }
    
    return;
}