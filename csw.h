//#include "includes.h"

typedef struct CSWs {
    int x;
    int y;
    int d;
    int life;
    int inertiaTimerIsRunning;
    double inertiaDirections[4];
    SDL_Texture* texture;
    void (*init)(struct CSWs * csw, int x, int y);
    void (*update)(struct CSWs * csw);
    void (*draw)(struct CSWs * csw);
} CSW;

void player_update();
void csw_draw(CSW csw);
