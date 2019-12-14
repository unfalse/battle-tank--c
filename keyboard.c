#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include "h.h"

struct callbacks {
    void (*left_key)();
    void (*right_key)();
    void (*up_key)();
    void (*down_key)();
    void (*pgup_key)();
    void (*pgdn_key)();
    void (*space_key)();
    void (*r_key)();
    void (*f_key)();
    void (*esc_key)();
    void (*f3_key)();
    void (*f2_key)();
    void (*f4_key)();
    void (*f5_key)();
    void (*f6_key)();
}



int keyboard_KeyEcho(t_sdl *sdl, struct callbacks cbs) {
    int gogogo;
    SDL_Event event;
    gogogo = 1;
    while (gogogo) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT) gogogo = 0;
        else if (event.type == SDL_KEYDOWN) {

            switch(event.key.keysym.sym){
                case SDLK_LEFT: cbs.left_key(); break;
                case SDLK_RIGHT: cbs.right_key(); break;
                case SDLK_UP: cbs.up_key(); break;
                case SDLK_DOWN: cbs.down_key(); break;
                case SDLK_PAGEUP: cbs.pgup_key(); break;
                case SDLK_PAGEDOWN: cbs.pgdn_key(); break;
                case SDLK_SPACE: cbs.space_key(); break;
                case SDLK_r: cbs.r_key(); break;
                case SDLK_f: cbs.f_key(); break;
                case SDLK_ESCAPE: cbs.esc_key(); gogogo=0; break;
                case SDLK_F3: cbs.f3_key(); break;
                case SDLK_F2: cbs.f2_key(); break;
                case SDLK_F4: cbs.f4_key(); break;
                case SDLK_F5: cbs.f5_key(); break;
                case SDLK_F6: cbs.f6_key(); break;
                default:
                    break;
            }
        }
    }
    return 0;
}

// left right up down pgup pgdn space r f esc F3 F2 F4 F5 F6
void Keyboard.KeyEcho(struct callbacks cbs);{KKeyEcho}
Begin
	xp:=x; yp:=y; // move outside (to user of this func)
                clearAim(xp,yp);
        	Aim;
End;

Procedure Keyboard.GraphRead;
Label again;
Var cx: shortint;
Begin
	MyWrite(50, 400, red, 'Please input filename ^');
	readln(filename);
	MyWrite(50, 400, 0, 'Please input filename ^');
	gotoxy(0,0);
End;

