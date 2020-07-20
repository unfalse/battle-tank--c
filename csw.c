#include "includes.h"
#include "csw.h"
#define csw_MAXIMUM_ACCELERATION 20

void csw_move(struct CSWs * csw, int d);
void player_draw(struct CSWs * csw);
void csw_inertia(struct CSWs * csw);

int getDirOpposites(int d) {
    int dirOpposites[4];
    dirOpposites[0] = 2;
    dirOpposites[1] = 3;
    dirOpposites[2] = 0;
    dirOpposites[3] = 1;
    return dirOpposites[d];
}

void player_setDirectionAndAddAccel(struct CSWs * csw, int d, double accel) {
    int dirOpposite = csw->inertiaDirections[getDirOpposites(d)];
    csw->d = d;
    if (dirOpposite > 0) {
        csw->inertiaDirections[getDirOpposites(d)] -= accel;
        if (dirOpposite < 0) {
            csw->inertiaDirections[getDirOpposites(d)] = 0;
        }
    } else {
        if (csw->inertiaDirections[d] + accel > csw_MAXIMUM_ACCELERATION) {
            return;
        }
        csw->inertiaDirections[d] += accel;
    }
}

void initPLAYER(struct CSWs * csw, int x, int y) {
    csw->x = x;
    csw->y = y;
    csw->life = 100;
    csw->inertiaTimerIsRunning = 0;
    csw->texture = graphics_LoadFromPNG("images/csw-mt9.png");
    csw->update = &player_update;
    csw->inertia = &csw_inertia;
    csw->draw = &player_draw;
    csw->move = &csw_move;
    csw->setDirectionAndAddAccel = &player_setDirectionAndAddAccel;
}

void csw_update(struct CSWs * csw) {
    
}

void initCPU(struct CSWs * csw, int x, int y) {
    csw->x = x;
    csw->y = y;
    csw->life = 100;
    csw->inertiaTimerIsRunning = 0;
    csw->texture = graphics_LoadFromPNG("images/csw-mt5.png");
    csw->update = &csw_update;
    csw->draw = &csw_draw;
    // csw.setDirectionAndAddAccel = &player_setDirectionAndAddAccel;
}

void player_update(struct CSWs * csw) {
    csw->inertia(csw);
}


double csw_getDirSum(struct CSWs * csw) {
    return csw->inertiaDirections[0] +
        csw->inertiaDirections[1] +
        csw->inertiaDirections[2] +
        csw->inertiaDirections[3];
}

void csw_draw(struct CSWs * csw) {
     graphics_RenderLoadedTexture(csw->texture, 300+csw->x, 200+csw->y, 20, 20);
}

void player_draw(struct CSWs * csw) {
     graphics_RenderLoadedTexture(csw->texture, 300+csw->x, 200+csw->y, 20, 20);
}

void csw_move(struct CSWs * csw, int d) {
    
}

void csw_inertia(struct CSWs * csw) {
    if (csw_getDirSum(csw) > 0 /*&& csw.inertiaTimerIsRunning == 1*/) {
        for (int d = 0; d < 4; d++) {
            if (csw->inertiaDirections[d] > 0) {
            } else {
                csw->inertiaDirections[d] = 0;
            }
            csw->move(csw, d);
        }
        csw->draw(csw);
    } else {
        // csw.inertiaTimerIsRunning = 0;
    }
}
