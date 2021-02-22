#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "includes.h"

LTimer capTimer;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

bool quit = false;

void events_Quit() {
    quit = true;
}

void events_Loop(void (*main_loop)(), void (*key_echo)()) {

    SDL_Event event;
    
    while (!quit) {

        //Start cap timer
        ltimer_Start(&capTimer);

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
        //If frame finished early
//        printf("\nStarted?: %d", capTimer.mStarted);
        int frameTicks = ltimer_GetTicks(&capTimer);
        // printf("\nFPS: %d", frameTicks);
        if( frameTicks < SCREEN_TICKS_PER_FRAME )
        {
            //printf("\nFPS: %d", frameTicks);
            //printf("\nWait: %d", SCREEN_TICKS_PER_FRAME - frameTicks); 
            //Wait remaining time
            SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
        }
    }
    
    return;
}
