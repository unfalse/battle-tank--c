//#include "includes.h"

#define COMPUTER 0
#define USER 1

typedef struct CSWs {
    int x;
    int y;
    int d;
    int iam;
    int life;
    int inertiaTimerIsRunning;
    double inertiaDirections[4];
    SDL_Texture* texture;
//     void (*initCPU)(struct CSWs * csw, int x, int y);
//     void (*initPLAYER)(struct CSWs * csw, int x, int y);
    void (*update)(struct CSWs * csw);
    void (*draw)(struct CSWs * csw);
    void (*fire)(struct CSWs * csw);
    void (*move)(struct CSWs * csw, int d);
    void (*inertia)(struct CSWs * csw);
    void (*setDirectionAndAddAccel)(struct CSWs * csw, int d, double accel);
} CSW;

extern CSW *cswArr[2];

void initPLAYER(struct CSWs * csw, int x, int y);
void initCPU(struct CSWs * csw, int x, int y);

void player_update(struct CSWs * csw);
void player_draw(struct CSWs * csw);
void csw_draw(struct CSWs * csw);
void cpu_draw(struct CSWs * csw);
void csw_fire(CSW * csw);
void csw_update(CSW * csw);

void csw_updatePV(CSW * csw);
void csw_setDirectionPV(CSW * csw, int d, double unused);