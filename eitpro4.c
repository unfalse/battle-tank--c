#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "includes.h"

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
    char colorpnt;          // { Счетчик цвета 				}
    char display[MAXX][MAXY]; // { Матрица изображения				}
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

void assembly_Init(void);
void assembly_Init() {
    bool successInit = graphics_Init();
//	data.filename='untitled';
	data.x=10;
    data.y=10;
    data.colorpnt=4;
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

void assembly_GameLoop() {
    graphics_Field();
    graphics_Decorate();
    graphics_Aim(data.x, data.y);
}

void assembly_Run() {
    graphics_GameLoop(assembly_GameLoop);
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

