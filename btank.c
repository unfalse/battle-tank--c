#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
//#include <unistd.h>
#include "includes.h"

SDL_Color graphics_editor_colors[COLORMAX];

struct callbacks keyboard_Callbacks;

typedef struct CSWs {
    int x;
    int y;
    int life;
    SDL_Texture* texture;
    void (*init)(int x, int y);
} CSW;

struct Settings {
    int passedFrames;
} settings;

void assembly_Init(void);
void assembly_ClearDisplay(void);
void assembly_SetKeyboardCallbacks();
void assembly_SetColors();
int myrandom(int min, int max);

//generate number in range [min,max)
int myrandom(int min, int max){
    int number = min + rand() % (max - min);
    return number; 
}

void esc_key() {
    events_Quit();
}

void assembly_SetKeyboardCallbacks() {
//    keyboard_Callbacks.left_key = &left_key;
//    keyboard_Callbacks.right_key = &right_key;
//    keyboard_Callbacks.up_key = &up_key;
//    keyboard_Callbacks.down_key = &down_key;
//    keyboard_Callbacks.space_key = &space_key;
    //keyboard_Callbacks.pgup_key = &pgup_key;
    //keyboard_Callbacks.pgdn_key = &pgdn_key;
    // keyboard_Callbacks.f3_key = &f3_key;
    keyboard_Callbacks.esc_key = &esc_key;
}

CSW player;
CSW cpu;

void assembly_Init() {
    bool successInit = graphics_Init();
    srand(time(NULL));
//    assembly_SetColors();

//    assembly_ClearDisplay();
    assembly_SetKeyboardCallbacks();

    player.x = 10;
    player.y = 10;
    player.life = 100;
    player.texture = graphics_LoadFromPNG("images/csw-mt5.png");

    cpu.x = 0;
    cpu.y = 0;
    cpu.life = 100;
    cpu.texture = graphics_LoadFromPNG("images/csw-mt9.png");

    //Start counting frames per second
	settings.passedFrames = 0;
	ltimer_Start();
}


void assembly_TanksMove() {
    int dx = myrandom(-10, 100);
    int dy = myrandom(-100, 12);
    graphics_RenderLoadedTexture(cpu.texture, 300+dx, 200+dy, 20, 20);
}

void assembly_GameLoop(SDL_Event event) {
	//Calculate and correct fps
	float avgFPS = settings.passedFrames / ( ltimer_GetTicks() / 1000.f );
	if( avgFPS > 2000000 )
	{
		avgFPS = 0;
	}
    
    graphics_RenderStart();

    graphics_ShowFPS(avgFPS);
    
    assembly_TanksMove();
    //graphics_RenderLoadedTexture(csw_mt5, 300, 200, 20, 20);
    
    graphics_RenderEnd();
    ++settings.passedFrames;
}

void assembly_Run() {
    events_Loop(assembly_GameLoop, keyboard_KeyEcho);
}

void assembly_SetColors() {
    printf("Setting colors...\n");
    memcpy(graphics_editor_colors, (SDL_Color[]) {
        {0x00,0x00,0x00,0x00}, // 0 black
        {0x00,0x00,0xaa,0xff}, // 1 blue
        {0x00,0xaa,0x00,0xff}, // 2 green
        {0x00,0xaa,0xaa,0xff}, // 3 cyan

	    {0xaa,0x00,0x00,0xff}, // 4 red
        {0xaa,0x00,0xaa,0xff}, // 5 magenta
        {0xaa,0x55,0x00,0xff}, // 6 brown
        {0xaa,0xaa,0xaa,0xff}, // 7 lightgray

        {0x55,0x55,0x55,0xff}, // 8 darkgray
        {0x55,0x55,0xff,0xff}, // 9 lightblue
        {0x55,0xff,0x55,0xff}, // 10 lightgreen
	    {0x55,0xff,0xff,0xff}, // 11 lightcyan

        {0xff,0x55,0x55,0xff}, // 12 lightred
        {0xff,0x55,0xff,0xff}, // 13 lightmagenta
        {0xff,0xff,0x55,0xff}, // 14 yellow
	    {0xff,0xff,0xff,0xff}  // 15 white
    },
  COLORMAX * sizeof *graphics_editor_colors);
    printf("sizeof colors: ");
    printf("%d\n", sizeof *graphics_editor_colors);
}



int main() {
    assembly_Init();
    assembly_Run();

    printf("graphics_Quit...\n");
    graphics_Quit();

    return 0;
}
