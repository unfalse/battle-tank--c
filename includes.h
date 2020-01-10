#include <stdbool.h>

#define COLORMAX 16
#define BEGX 70
#define BEGY 50
#define MAXX 20
#define MAXY 20
#define FILEEXT '.c20'

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define REN 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

// Graphics

bool graphics_Init(void);
void graphics_Aim(int, int);
void graphics_Caption();
void graphics_Texture();
void graphics_ClearAim(int, int);
void graphics_CurrColr();               //	{ Показывает текущий цвет		}
void graphics_Decorate();               //	{ Оформление				}
//void graphics_DrawData(SDL_Color *);    //  { Рисует содержимое массива изображения }
void graphics_DrawData(SDL_Color [][MAXY]);    //  { Рисует содержимое массива изображения }
void graphics_DrawAsReal(SDL_Color *);  //	{ Рисует рисунок таким, каким он будет	}
void graphics_EraseImg();               //	{ Стирает всё изображение		}
void graphics_FillImg();                //	{ Заливает всю картинку выбранным цветом}
void graphics_Field();                  //  { Рисует поле для редактирования	}
// void graphics_FillCell(int, int, );  // { Закрашивает клетку			}
void graphics_ShowXY();                 // { Показывает текущие координаты курсора	}
void graphics_ShowFPS(float);
void graphics_LOGO();
void graphics_Help();
void graphics_MyWrite();
void graphics_GameLoop(void (*game_loop)());
void graphics_RenderStart();
void graphics_RenderEnd();
void graphics_Quit();

SDL_Color graphics_editor_colors[COLORMAX];

// Events

void events_Loop(void (*main_loop)(), void (*key_echo)());

// LTimer
//Gets the timer's time
Uint32 ltimer_GetTicks();
void ltimer_Start();

// Keyboard

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
} keyboard_Callbacks; 

void keyboard_KeyEcho(SDL_Event event);
