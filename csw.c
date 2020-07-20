#include "includes.h"
#include "csw.h"
#define csw_MAXIMUM_ACCELERATION 20

int getDirOpposites(int d) {
    int dirOpposites[4];
    dirOpposites[0] = 2;
    dirOpposites[1] = 3;
    dirOpposites[2] = 0;
    dirOpposites[3] = 1;
    return dirOpposites[d];
}

void player_update() {
    double ACCEL = 0.3;
    if (leftPressed == 1) {
        // d=2
        // player.x--;
        player_setDirectionAndAddAccel(2, ACCEL);
    }
    if (upPressed == 1) {
        // d=3
        // player.y--;
        player_setDirectionAndAddAccel(3, ACCEL);
    }
    if (rightPressed == 1) {
        // d=0
        // player.x++;
        player_setDirectionAndAddAccel(0, ACCEL);
    }
    if (downPressed == 1) {
        // d=1
        // player.y++;
        player_setDirectionAndAddAccel(1, ACCEL);
    }
    
    //csw_inertia(player);
}


void csw_update(struct CSWs * csw) {
    
}

double csw_getDirSum(struct CSW csw) {
    return csw.inertiaDirections[0] +
        csw.inertiaDirections[1] +
        csw.inertiaDirections[2] +
        csw.inertiaDirections[3];
}

void player_setDirectionAndAddAccel(int d, double accel) {
    int dirOpposite = player.inertiaDirections[getDirOpposites(d)];
    player.d = d;
    if (dirOpposite > 0) {
        player.inertiaDirections[getDirOpposites(d)] -= accel;
        if (dirOpposite < 0) {
            player.inertiaDirections[getDirOpposites(d)] = 0;
        }
    } else {
        if (player.inertiaDirections[d] + accel > csw_MAXIMUM_ACCELERATION) {
            return;
        }
        player.inertiaDirections[d] += accel;
    }
}


void csw_draw(CSW csw) {
     graphics_RenderLoadedTexture(csw.texture, 300+csw.x, 200+csw.y, 20, 20);
}

void csw_move(CSW csw, int d) {
    
}

void csw_inertia(CSW csw) {
    if (csw_getDirSum(csw) > 0 /*&& csw.inertiaTimerIsRunning == 1*/) {
        for (int d = 0; d < 4; d++) {
            if (csw.inertiaDirections[d] > 0) {
            } else {
                csw.inertiaDirections[d] = 0;
            }
            csw_move(csw, d);
        }
        csw_draw(csw);
    } else {
        // csw.inertiaTimerIsRunning = 0;
    }
}

void cpu_draw(int x, int y, SDL_Texture* texture) {
     graphics_RenderLoadedTexture(texture, 300+x, 200+y, 20, 20);
}
