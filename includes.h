bool graphics_Init(void);
void graphics_Aim(int, int);
void graphics_Caption();
void graphics_Texture();
void graphics_ClearAim(int, int);
void graphics_CurrColr();           //	{ Показывает текущий цвет		}
void graphics_Decorate();           //	{ Оформление				}
void graphics_DrawData();           //  { Рисует содержимое массива изображения }
void graphics_DrawAsReal();         //	{ Рисует рисунок таким, каким он будет	}
void graphics_EraseImg();           //	{ Стирает всё изображение		}
void graphics_FillImg();            //	{ Заливает всю картинку выбранным цветом}
void graphics_Field();              //  { Рисует поле для редактирования	}
void graphics_FillCell();           // { Закрашивает клетку			}
void graphics_ShowXY();             // { Показывает текущие координаты курсора	}
void graphics_LOGO();
void graphics_Help();
void graphics_MyWrite();
void graphics_GameLoop(void (*game_loop)());
void graphics_Quit();

#define BEGX 70
#define BEGY 50
#define MAXX 20
#define MAXY 20
#define FILEEXT '.c20'
