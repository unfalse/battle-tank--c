#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "includes.h"

void assembly_Init(void);
void assembly_ClearDisplay(void);
void assembly_SetKeyboardCallbacks();
void assembly_SetColors();
void assembly_SetCurrentColor(int);
void assembly_PutPixel();

void left_key();
void right_key();
void up_key();
void down_key();
void space_key();
void pgup_key();

int rx, ry;

struct Data {
	char bt;
	bool isfls;				// { Выбран ли режим управления файлами		}
//	bytefile fimg;			// { Текущий файл					}
	bool load;				// { Индикатор открытия файла			}
	bool find;				// { Индикатор поиска файла			}
	bool save;				// { Индикатор сохранения файла			}
	bool txr;
    bool exiting;           // { Индикатор ухода со станции			}
    int x;                  // { Счетчик ячеек по горизонтали			}
    int y;                  // { Счетчик ячеек по вертикали 			}
    
    // char colorpnt;          // { Счетчик цвета 				}
    int currentColorNum;
    // SDL_Color editor_colors[COLORMAX];
	SDL_Color currentColor;

    SDL_Color display[MAXX][MAXY]; // { Матрица изображения				}

    int countedFrames;
/*
		savs	: boolean;
		actclr	: boolean;				{ Инд. режима управления цветом			}
		decclr	: boolean;				{ Инд. уменьшения счетчика текущего цвета	}
		incclr	: boolean;				{ Инд. увеличения счетчика текущего цвета     	}
		erase	: boolean;				{ Инд. уничтожения текущего изображения       	}
		fill	: boolean;				{ Инд. заливки всей области			}
		putclr	: boolean;				{ Инд. установки цвета текущей ячейки         	}
		IsClose : boolean;				{ Инд. того что файл не состыкован со станцией	}
		display : array[0..MaxX-1, 0..MaxY-1] of byte;	

		key	: char;					{ Датчик клавиши 				}
		pc	: boolean;				{ Инд. нажатия клавиши 				}
*/
		char* filename;				// { Имя файла 					}
		short modify;
} data;

int GetRX();
int GetRY();

void assembly_Init() {
    bool successInit = graphics_Init();
    assembly_SetColors();
//	data.filename='untitled';
	data.x=10;
    data.y=10;
    // data.colorpnt=4;
	assembly_SetCurrentColor(4);
    assembly_ClearDisplay();
    assembly_SetKeyboardCallbacks();

        	//Start counting frames per second
	data.countedFrames = 0;
	ltimer_Start();
/*
	isfls:=false;
	save:=false;
	load:=false;
	find:=false;
	fill:=false;
*/
//    graphics_Decorate();
/*
	graphics_Aim();
	graphics_Drawdata();
	graphics_Drawasreal();
	files_FindFIMG();
	graphics_help();
	graphics_LOGO();
*/
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

void assembly_SetCurrentColor(int colorNum) {
	data.currentColorNum = colorNum;
	if (colorNum > COLORMAX - 1) {
		data.currentColorNum = 0;
	}
	data.currentColor = graphics_editor_colors[data.currentColorNum];
}

void assembly_ClearDisplay() {
    for (int i=0; i<MAXX; i++) {
        for (int j=0; j<MAXY; j++) {
            data.display[i][j].r = 0;
            data.display[i][j].g = 0;
            data.display[i][j].b = 0;
            data.display[i][j].a = 0;
        }
    }
}

void left_key() {
    if (data.x - 1 >= 0) {
        data.x--;
    }
}

void right_key() {
    if (data.x + 1 < MAXX) {
        data.x++;
    }
}

void up_key() {
    if (data.y - 1 >= 0) {
        data.y--;
    }
}

void down_key() {
    if (data.y + 1 < MAXY) {
        data.y++;
    }
}

void assembly_PutPixel() {
    data.display[data.x][data.y] = data.currentColor;
}

void space_key() {
	assembly_PutPixel();
}

void pgup_key() {
    assembly_SetCurrentColor(++data.currentColorNum);
}

void pgdn_key() {
    assembly_SetCurrentColor(--data.currentColorNum);
}

void assembly_SetKeyboardCallbacks() {
    keyboard_Callbacks.left_key = &left_key;
    keyboard_Callbacks.right_key = &right_key;
    keyboard_Callbacks.up_key = &up_key;
    keyboard_Callbacks.down_key = &down_key;
    keyboard_Callbacks.space_key = &space_key;
    keyboard_Callbacks.pgup_key = &pgup_key;
    keyboard_Callbacks.pgdn_key = &pgdn_key;
}

void assembly_GameLoop(SDL_Event event) {

	//Calculate and correct fps
	float avgFPS = data.countedFrames / ( ltimer_GetTicks() / 1000.f );
	if( avgFPS > 2000000 )
	{
		avgFPS = 0;
	}
    
    // keyboard_KeyEcho(event);
    graphics_RenderStart();

    graphics_ShowFPS(avgFPS);
    graphics_ShowXY(data.x, data.y);
    graphics_Field();
    graphics_Decorate();
    graphics_Aim(data.x, data.y);
    graphics_DrawData(data.display);
    graphics_DrawAsReal((SDL_Color *)data.display);
    
    graphics_RenderEnd();
    ++data.countedFrames;
}

void assembly_Run() {
    // not working, giving an error
    // events_Loop(graphics_GameLoop(assembly_GameLoop));
    events_Loop(assembly_GameLoop, keyboard_KeyEcho);
/*
    do{
        keyboard_KeyEcho(sdl, callbacks);
        graphics_ShowXY();
        // Handler;
        graphics_CurrColr();
        graphics_DrawAsReal();
    } while(exiting!=true);
*/
}

/* very bad idea!
void MainHandler();
void MainHandler() {

	if (isfls == true) { // Actions with files and exiting }
               	If load=true then begin GraphRead; OpenFIMG; DrawData; load:=false; end
		Else    If Save=true then begin SaveFIMG; save:=false; end
			Else if savs=true then begin GraphRead; SaveFIMG; savs:=false; end
			Else If find=true then begin FindFIMG; find:=false; end;
		isfls:=false;
} 
               	Begin

		End;
// {-===-===] Color change }
	If actclr=true then
		Begin
		If incclr=true then begin if colorpnt<>15 then inc(colorpnt); incclr:=false; end
		Else	If decclr=true then begin if colorpnt<>0 then dec(colorpnt); decclr:=false; end
			Else	If Txr=true then begin Texture; txr:=false; end;
			If Putclr=true then begin fillcell; display[x,y]:=colorpnt; Putclr:=false; end;
                End;

}
*/

/*
 * Lesson 0: Test to make sure SDL is setup properly
 */
int main(){
/*
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %d\n", SDL_GetError());
        return 1;
    }
*/

    assembly_Init();
    assembly_Run();

    graphics_Quit();

    return 0;
}

