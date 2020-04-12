#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "includes.h"

bool quit = false;

void events_Quit() {
    quit = true;
}

void events_Loop(void (*main_loop)(), void (*key_echo)()) {

    SDL_Event event;

    while (!quit) {
        
        // SDL_WaitEvent(&event);

        while( SDL_PollEvent(&event) != 0) {
            key_echo(event);
            // printf("polling event...\n");
            // User requests quit
            if(event.type == SDL_QUIT) {
                printf("quitting...\n");
                quit = true;
			}
            
		}
        
        // printf("wait ended...\n");

        main_loop(event);

        //SDL_Delay(100);

    }
    
    return;
}