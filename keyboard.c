#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "includes.h"

void keyboard_KeyEcho(SDL_Event event) {

    if (event.type == SDL_KEYDOWN) {
        // printf("keydown! %d\n",event.key.keysym.scancode); 
        switch(event.key.keysym.sym){
            case SDLK_SPACE:    keyboard_Callbacks.space_key(); break;
            case SDLK_LEFT:     keyboard_Callbacks.left_key(); break;
            case SDLK_RIGHT:    keyboard_Callbacks.right_key(); break;
            case SDLK_UP:       keyboard_Callbacks.up_key(); break;
            case SDLK_DOWN:     keyboard_Callbacks.down_key(); break;
            case SDLK_PAGEUP:   keyboard_Callbacks.pgup_key(); break;
            case SDLK_PAGEDOWN: keyboard_Callbacks.pgdn_key(); break;
            case SDLK_r:        keyboard_Callbacks.r_key(); break;
            case SDLK_f:        keyboard_Callbacks.f_key(); break;
            case SDLK_ESCAPE:   keyboard_Callbacks.esc_key(); break;
            case SDLK_F3:       keyboard_Callbacks.f3_key(); break;
            case SDLK_F2:       keyboard_Callbacks.f2_key(); break;
            case SDLK_F4:       keyboard_Callbacks.f4_key(); break;
            case SDLK_F5:       keyboard_Callbacks.f5_key(); break;
            case SDLK_F6:       keyboard_Callbacks.f6_key(); break;
            default:
                break;
        }
    }

    return ;
}

// left right up down pgup pgdn space r f esc F3 F2 F4 F5 F6
// void keyboard_KeyEcho(struct callbacks cbs) { // ;{KKeyEcho}
/*
    Begin
	xp:=x; yp:=y; // move outside (to user of this func)
                clearAim(xp,yp);
        	Aim;
End;
*/
//}

/*
Procedure Keyboard.GraphRead;
Label again;
Var cx: shortint;
Begin
	MyWrite(50, 400, red, 'Please input filename ^');
	readln(filename);
	MyWrite(50, 400, 0, 'Please input filename ^');
	gotoxy(0,0);
End;
*/