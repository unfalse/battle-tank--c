#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "includes.h"

void graphics_Rectangle(int, int, int, int, SDL_Color);
void graphics_FillCell(int, int, SDL_Color);
void graphics_Line(int, int, int, int, SDL_Color);
bool graphics_LoadMedia();
void graphics_RenderTextureAdvanced(int, int, SDL_Rect*, double, SDL_Point*, SDL_RendererFlip);
void graphics_RenderTexture(int, int);
bool graphics_LoadFromRenderedText(char*, SDL_Color);
void graphics_TextFree();
void graphics_OutTextXY(int, int, char*, SDL_Color);
void graphics_PutPixel(int, int, SDL_Color);
//void graphics_PutPixels(SDL_Point*, SDL_Color, int);
void graphics_SetPalette();
void graphics_Help();
void graphics_SetColor(int);
Uint32 graphics_GetPixel(SDL_Surface*, int, int);

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct graphics_struct {
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    TTF_Font *gFont;
	//The actual hardware texture
	SDL_Texture* mTexture;
	//Image dimensions
	int mWidth;
	int mHeight;
    SDL_Color currentColor;
} graphics;

bool graphics_Init() {
	//Initialization flag
	bool success = true;

    graphics.gWindow = NULL;
    graphics.gRenderer = NULL;

/*
   memcpy(data.editor_colors, (SDL_Color[]) {
        { eepcal[1], eepcal[2] }, {-1, -1}
    },
  sizeof *data.editor_colors);
     
         data.editor_colors[0] = {0x00,0x00,0x00,0x00}; // 0
    data.editor_colors[1] = {0x00,0x00,0xaa,0xff};
    data.editor_colors[2] = {0x00,0xaa,0x00,0xff}; // 2
    data.editor_colors[3] = {0x00,0xaa,0xaa,0xff};

    data.editor_colors[4] = {0xaa,0x00,0x00,0xff}; // 4 red
    data.editor_colors[5] = {0xaa,0x00,0xaa,0xff}; // 5 magenta
    data.editor_colors[6] = {0xaa,0x55,0x00,0xff}; // 6 brown
    data.editor_colors[7] = {0xaa,0xaa,0xaa,0xff}; // 7 lightgray

    data.editor_colors[8] = {0x55,0x55,0x55,0xff}; // 8 darkgray
    data.editor_colors[9] = {0x55,0x55,0xff,0xff}; // 9
    data.editor_colors[10] = {0x55,0xff,0x55,0xff}; // 10
    data.editor_colors[11] = {0x55,0xff,0xff,0xff}; // 11

    data.editor_colors[12] = {0xff,0x55,0x55,0xff}; // 12
    data.editor_colors[13] = {0xff,0x55,0xff,0xff}; // 13
    data.editor_colors[14] = {0xff,0xff,0x55,0xff}; // 14
    data.editor_colors[15] = {0xff,0xff,0xff,0xff};  // 15
     */
    
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		graphics.gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( graphics.gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			graphics.gRenderer = SDL_CreateRenderer( graphics.gWindow, -1, SDL_RENDERER_SOFTWARE );
			if( graphics.gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}

            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(IMG_INIT_PNG)&imgFlags)) {
                printf("SDL IMG_Init error!\n");
            }

             //Initialize SDL_ttf
			if( TTF_Init() == -1 )
			{
				printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
				success = false;
			}

            graphics.mTexture = NULL;
	        graphics.mWidth = 0;
	        graphics.mHeight = 0;

            //Load media
			if( !graphics_LoadMedia()) {
				printf( "Failed to load media!\n" );
			}
		}
	}

	return success;
}

void graphics_Quit() {
	//Free loaded images
	// gTextTexture.free();

	//Free global font
    printf("CloseFont...\n");
	TTF_CloseFont( graphics.gFont );
    graphics.gFont = NULL;

	//Destroy window
    printf("SDL_DestroyRenderer...\n");
	SDL_DestroyRenderer( graphics.gRenderer );
    printf("SDL_DestroyWindow...\n");
	SDL_DestroyWindow( graphics.gWindow );
	graphics.gWindow = NULL;
	graphics.gRenderer = NULL;

	//Quit SDL subsystems
    printf("TTF_Quit...\n");
	TTF_Quit();
    printf("IMG_Quit...\n");
	IMG_Quit();
    printf("SDL_Quit...\n");
    SDL_Quit();
}

/*
void graphics_SetPalette() {
    int intColors = 16;
    //SDL_Palette *palette = (SDL_Palette *)malloc(sizeof(colors[0])*intColors);
    //SDL_SetPaletteColors(palette, colors, 0, intColors);
    // SDL_SetSurfacePalette(surface, palette);
}
*/

void graphics_ShowFPS(float fps) {
    char fps_str[20];
    sprintf(fps_str, "%f", fps);
    SDL_Color color = { 0, 255, 0, 255 };
    graphics_OutTextXY(20, 20, fps_str, color);
}

void graphics_RenderTextureAdvanced( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, graphics.mWidth, graphics.mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( graphics.gRenderer, graphics.mTexture, clip, &renderQuad, angle, center, flip );
}

SDL_Texture* graphics_LoadFromPNG(const char* file) {
    SDL_Surface * image = IMG_Load(file);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(graphics.gRenderer, image);
    return texture;
}

void graphics_RenderLoadedTexture(SDL_Texture* texture, int x, int y, int width, int height) {
    SDL_Rect dstRect = { x, y, width, height };
    SDL_RenderCopy(graphics.gRenderer, texture, NULL, &dstRect);
}

void graphics_RenderTexture(int x, int y) {
    graphics_RenderTextureAdvanced(x, y, NULL, 0.0, NULL, SDL_FLIP_NONE);
}

bool graphics_LoadMedia() {
	//Loading success flag
	bool success = true;

	//Open the font
	graphics.gFont = TTF_OpenFont( "terminusbold.ttf", 14 );
	if( graphics.gFont == NULL )
	{
		printf( "Failed to load terminusbold font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	return success;
}

bool graphics_LoadFromRenderedText( char* textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	graphics_TextFree();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( graphics.gFont, textureText, textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        graphics.mTexture = SDL_CreateTextureFromSurface( graphics.gRenderer, textSurface );
		if( graphics.mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			graphics.mWidth = textSurface->w;
			graphics.mHeight = textSurface->h;
		}

		//Get rid of old surface
		//SDL_FreeSurface( textSurface );
	}
	
	//Return success
	return graphics.mTexture != NULL;
}

void graphics_TextFree()
{
	//Free texture if it exists
	if( graphics.mTexture != NULL )
	{
		SDL_DestroyTexture( graphics.mTexture );
		graphics.mTexture = NULL;
		graphics.mWidth = 0;
		graphics.mHeight = 0;
	}
}

void graphics_GameLoop(void (*game_loop)()) {
    SDL_SetRenderDrawColor(graphics.gRenderer, 0, 0, 0, 0);
    SDL_RenderClear(graphics.gRenderer);
    game_loop();
    SDL_RenderPresent(graphics.gRenderer);
}

void graphics_RenderStart() {
    SDL_SetRenderDrawColor(graphics.gRenderer, 0, 0, 0, 0);
    SDL_RenderClear(graphics.gRenderer);
}

void graphics_RenderEnd() {
    SDL_RenderPresent(graphics.gRenderer);
}

void graphics_ShowXY(int x, int y) {
    char numx[10], numy[10];
    sprintf(numx, "%d", x);
    sprintf(numy, "%d", y);
    SDL_Color color = { 0, 255, 0, 255 };
    graphics_OutTextXY(70, 35, numx, color);
    graphics_OutTextXY(120, 35, numy, color);
/*
    setcolor(BLACK);
	outtextxy(70,40,'████████████');
	str(getry,iy);
	str(getrx,ix);
	setcolor(cyan);
	outtextxy(70,40,ix);
	outtextxy(120,40,iy);
*/
}

void graphics_MyWrite(int x, int y, int color, char* out) {
/*
begin
	setcolor(color);
	OutTextXY(x,y,out);
end;
*/
}

//void graphics_DrawData(SDL_Color *display) {// {GDrawData}
void graphics_DrawData(SDL_Color display[][MAXY]) {// {GDrawData}
    int rx=0, ry=0;
    for (rx=0; rx<MAXX; rx++) {
        for (ry=0; ry<MAXY; ry++) {
            graphics_FillCell(rx, ry, display[rx][ry]);
        }
    }
}

void graphics_Field() { //{GField}
    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Point points[(MAXX+1) * (MAXY+1)];

    for(int x1=0; x1 < MAXX+1; x1++) {
        for(int y1=0; y1 < MAXY+1; y1++) {
            points[y1 + (x1*(MAXY+1))].x = x1 * 10 + BEGX;
            points[y1 + (x1*(MAXY+1))].y = y1 * 10 + BEGY;
        }
    }

    graphics_PutPixels(points, color, (MAXX+1)*(MAXY+1));
}

void graphics_Decorate() {// {GDecorate}
    //Clear screen
    SDL_SetRenderDrawColor(graphics.gRenderer, 0x00, 0x00, 0x00, 0x00);
    // SDL_RenderClear(graphics.gRenderer);

    SDL_Color color = { 51, 255, 255, 255 };
    graphics_Rectangle(400 - 2, 2, MAXX, MAXY, color);

    SDL_Color color2 = { 0, 127, 0, 255 }; // setcolor(green);
    graphics_Rectangle(40*10+BEGX+1-2, 20*10+BEGY+1-2, 40*10+BEGX+9+2 - 40*10+BEGX+1-2, 20*10+BEGY+9+2 - 20*10+BEGY+1-2, color2);
    graphics_Line(40*10+BEGX+1-44, 20*10+BEGY+1+5, 40*10+BEGX+1-2, 20*10+BEGY+1+5, color2);

    SDL_Color colorLine = { 0, 255, 0, 255 };
    graphics_Line(40*10+BEGX+1-44, 20*10+BEGY+1+5, 40*10+BEGX+1-2, 20*10+BEGY+1+5, colorLine);

    graphics_OutTextXY(40*10+BEGX+1-100, 20*10+BEGY+1, "Pattern", colorLine);
/*
	setcolor(Cyan);
	rectangle(400-2,2,400+maxx+1, 4+maxy+3);
	setcolor(green);
	rectangle(40*10+begx+1-2, 20*10+begy+1-2, 40*10+begx+9+2, 20*10+begy+9+2);
	line(40*10+begx+1-44, 20*10+begy+1+5, 40*10+begx+1-2, 20*10+begy+1+5);
	setcolor(lightgreen);
	outtextxy(40*10+begx+1-100, 20*10+begy+1,'Pattern');
*/
}

void graphics_Aim(int x, int y) {
    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Point points[4] = {
        {x*10+BEGX+5,  y*10+BEGY},     // {Vertical up}
        {x*10+BEGX+5,  y*10+BEGY+10},  // {Vertical down}
        {x*10+BEGX+10, y*10+BEGY+5},   //{Horizont }
        {x*10+BEGX,    y*10+BEGY+5}
    };

    graphics_PutPixels(points, color, 4);
    // graphics_PutPixel(x*10+BEGX+5,  y*10+BEGY,    color);     // {Vertical up}
    // graphics_PutPixel(x*10+BEGX+5,  y*10+BEGY+10, color);  // {Vertical down}
    // graphics_PutPixel(x*10+BEGX+10, y*10+BEGY+5,  color);   //{Horizont }
    // graphics_PutPixel(x*10+BEGX,    y*10+BEGY+5,  color);
}

void graphics_OutTextXY(int x, int y, char* text, SDL_Color color) {
    if( !graphics_LoadFromRenderedText( text, color ) )
	{
		printf( "Failed to render text texture!\n" );
	}
    graphics_RenderTexture(x, y);
}

void graphics_Line(int x, int y, int x2, int y2, SDL_Color color) {
    SDL_SetRenderDrawColor(graphics.gRenderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(graphics.gRenderer, x, y, x2, y2);
}

void graphics_Rectangle(int x, int y, int w, int h, SDL_Color color) {
//    printf("%d %d %d %d\n", x, y, w, h);
    SDL_Rect outlineRect = { x, y, w, h };
    SDL_SetRenderDrawColor(graphics.gRenderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(graphics.gRenderer, &outlineRect);
}

void graphics_FillCell(int x, int y, SDL_Color color) { // {GFillCell}
    SDL_Rect bar = { x * 10 + BEGX + 1, y * 10 + BEGY + 1, 8, 8 };
    // printf("%d %d %d %d |", color.r, color.g, color.b, color.a);
    SDL_SetRenderDrawColor(graphics.gRenderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(graphics.gRenderer, &bar);
//    setfillstyle(solidfill, colorpnt);
//    bar(getrx*10+begx+1, getry*10+begy+1, getrx*10+begx+9, getry*10+begy+9);
}

void graphics_PutPixel(int x, int y, SDL_Color color) {
    SDL_SetRenderDrawColor(graphics.gRenderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(graphics.gRenderer, x, y);
}

void graphics_PutPixels(SDL_Point* points, SDL_Color color, int count) {
    // printf("%d", points[0].x);
    SDL_SetRenderDrawColor(graphics.gRenderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoints(graphics.gRenderer, points, count);
}

void graphics_DrawAsReal(SDL_Color *display) { // {GDrawAsReal}
    for (int rx = 0; rx < MAXX; rx++) {
		for (int ry = 0; ry < MAXY; ry++){
			graphics_PutPixel(rx + 400, ry + 5, *((display + rx * MAXY) + ry));
        }
    }
}

void graphics_DrawAsRealAtXY(SDL_Color *display, int x, int y) { // {GDrawAsReal}
    for (int rx = 0; rx < MAXX; rx++) {
		for (int ry = 0; ry < MAXY; ry++){
			graphics_PutPixel(rx + x, ry + y, *((display + rx * MAXY) + ry));
        }
    }
}

Uint32 graphics_GetPixel(SDL_Surface *surface, int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

switch (bpp)
{
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
            break;

        case 4:
            return *(Uint32 *)p;
            break;

        default:
            return 0;       /* shouldn't happen, but avoids warnings */
      }
}

void graphics_ClearAim(int x1, int y1){
/*
begin
		putpixel(x1*10+begx+5, y1*10+begy, 0);
		putpixel(x1*10+begx+10, y1*10+begy+5, 0);
		putpixel(x1*10+begx+5, y1*10+begy+10, 0);
		putpixel(x1*10+begx, y1*10+begy+5, 0);
end;
*/
}

void graphics_Caption() {
/*
	Begin
		MyWrite(100,20,0,'████████');
		MyWrite(100,20,lightgreen,filename);
	End;
*/
}

void graphics_Texture() {
    int	tx,ty;
	char color;
/*
Begin
	for tx:=1 to 6 do
        	for ty:=1 to 6 do for rx:=0 to maxx-1 do
			for ry:=0 to maxy-1 do begin
				color:=display[rx,ry];
				putpixel(rx+300+(tx*20), ry+30+(ty*20), color);
			end;
End;
*/
}

void graphics_Help() {
    int y = 0;
    for (y=413; y<480; y++) {
        graphics_Line(0, y, 640, y, graphics_editor_colors[DARKGRAY]);
    }
    graphics_Line(0, 398, 640, 398, graphics_editor_colors[GREEN]);
    
    graphics_OutTextXY(10, 400, "_=-       Colors        |      Files          |          Miscellaneous    -=_", graphics_editor_colors[WHITE]);
    graphics_OutTextXY(10, 412, "PgUp  - increase color  |  F2 - save file     |  F6  - turn the textures on  ", graphics_editor_colors[LIGHTGRAY]);
	graphics_OutTextXY(10, 424, "PgDn  - decrease color  |  F3 - open file     |  Esc - exit                  ", graphics_editor_colors[LIGHTGRAY]);
	graphics_OutTextXY(10, 436, "Space - put color       |  F4 - find file     |       Cursor keys            ", graphics_editor_colors[LIGHTGRAY]);
	graphics_OutTextXY(10, 448, "r     - erase image     |  F5 - save file as  |  Move the cursor             ", graphics_editor_colors[LIGHTGRAY]);
	graphics_OutTextXY(10, 460, "f     - fill image with selected color        |", graphics_editor_colors[LIGHTGRAY]);
}

void graphics_LOGO() {
    int x, y, col;
    graphics_OutTextXY(475, 5, "nopefish developments", graphics_editor_colors[LIGHTBLUE]);
    graphics_OutTextXY(200, 5, "EDITPRO V.1.5", graphics_editor_colors[WHITE]);
    for(x=199; x<303; x++) {
        for(y=4; y<12; y++) {
            
        }
    }
//var	x,y,col:integer;
// begin
/*
	setcolor(LIGHTBLUE);
	outtextxy(475, 5, '_=- TUFTA SOFT -=_');
	setcolor(15);
	outtextxy(200, 5, 'EDITPRO V.1.5');
	For x:=199 to 303 do
        	For y:=4 to 12 do
		begin
		col:=getpixel(x,y);
		col:=col xor red;
                PutPixel(x,y,col);
		end;
end;
*/
}


/*

Procedure LOGO;
var	x,y,col:integer;
begin
	setcolor(LIGHTBLUE);
	outtextxy(475, 5, '_=- TUFTA SOFT -=_');
	setcolor(15);
	outtextxy(200, 5, 'EDITPRO V.1.5');
	For x:=199 to 303 do
        	For y:=4 to 12 do
		begin
		col:=getpixel(x,y);
		col:=col xor red;
                PutPixel(x,y,col);
		end;
end;
        
Procedure Graphics.CurrColr;{GCurrColr}
Var 	px,py: Integer;
Begin
	px:=x; py:=y; x:=40; y:=20; fillcell; x:=px; y:=py;
End;



Procedure Graphics.EraseImg;{GEraseImg}
var	px,py:integer;
	col: byte;
	Begin
		col:=colorpnt;
		px:=x; py:=y;
		for rx:=0 to maxx-1 do
			for ry:=0 to maxy-1 do begin
                                display[rx,ry]:=0;
				colorpnt:=0; x:=rx;y:=ry;
				FillCell;
			end;
		x:=px; y:=py; colorpnt:=col;
	End;
*/
void graphics_FillImg() {
/*
var	px,py:integer;
begin
		px:=x; py:=y;
		for rx:=0 to maxx-1 do
			for ry:=0 to maxy-1 do begin
                                display[rx,ry]:=colorpnt;
				x:=rx;y:=ry;
				FillCell;
			end;
		x:=px; y:=py;
end;
*/
}
