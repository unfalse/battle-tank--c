#include "includes.h"
#include "csw.h"

#define csw_MAXIMUM_ACCELERATION 20
#define csw_CSWSPEED 0

void csw_move(struct CSWs * csw, int d);
void player_draw(struct CSWs * csw);
void csw_inertia(struct CSWs * csw);

int *base_getVXY(int d);

int getDirOpposites(int d) {
    int dirOpposites[4];
    dirOpposites[0] = 2;
    dirOpposites[1] = 3;
    dirOpposites[2] = 0;
    dirOpposites[3] = 1;
    return dirOpposites[d];
}

CSW *cswArr[2];

void player_setDirectionAndAddAccel(CSW * csw, int d, double accel) {
    int dirOpposite = csw->inertiaDirections[getDirOpposites(d)];
    csw->d = d;
//     printf("setDirectionAndAddAccel!\n");
//     printf("iD = %f\n", csw->inertiaDirections[2]);
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

void csw_setDirectionPV(CSW * csw, int d, double unused) {
    csw->d = d;
}

bool csw_CheckCSW(int x, int y) {
    int cnt = 0;
    while(cnt < 2) {
        if (cswArr[cnt]->x == x && cswArr[cnt]->y == y) {
            return true;
        }
        cnt++;
    }
    return false;
}

void csw_updatePV(CSW * csw) {
    printf("\ninside csw_updatePV!");
    if (csw->life <= 0) {
        csw->life = 0;
    } else {
        //if (csw->iam == USER) {
            printf("\niam=%d, d=%d", csw->iam, csw->d);
            int *nvxy = base_getVXY(csw->d);
            int vx = nvxy[0];
            int vy = nvxy[1];
            if ((csw->x + vx) > 20 || (csw->x + vx < 1)) {
                vx = 0;
            }
            if ((csw->y + vy) > 20 || (csw->y + vy < 1)) {
                vy = 0;
            }
            if(!(vx == 0 && vy == 0)) {
                if (csw_CheckCSW(csw->x + vx, csw->y + vy) == true) {
                    vx = 0;
                    vy = 0;
                }
            }
            csw->x = csw->x + vx;
            csw->y = csw->y + vy;
        //}
    }
    csw->draw(csw);
}

void csw_firePV(CSW * csw) {

}

void csw_fire(CSW * csw) {

}

void initPLAYER(CSW * csw, int x, int y) {
    csw->d = 5;
    csw->iam = USER;
    csw->x = x;
    csw->y = y;
    csw->life = 100;
    csw->inertiaTimerIsRunning = 0;
    csw->texture = graphics_LoadFromPNG("images/csw-mt9.png");

    csw->inertia = &csw_inertia;
    csw->draw = &player_draw;
    csw->move = &csw_move;
    csw->setDirectionAndAddAccel = &player_setDirectionAndAddAccel;
    
    if (PASCAL_VERSION == 0) {
        csw->update = &player_update;
    } else {
        csw->update = &csw_updatePV;
        csw->setDirectionAndAddAccel = &csw_setDirectionPV;
    }
    cswArr[0] = csw;
}

void initCPU(CSW * csw, int x, int y) {
    csw->iam = COMPUTER;
    csw->d = 5;
    csw->x = x;
    csw->y = y;
    csw->life = 100;
    csw->inertiaTimerIsRunning = 0;
    csw->texture = graphics_LoadFromPNG("images/csw-mt5.png");
    
    csw->draw = &csw_draw;
    // csw.setDirectionAndAddAccel = &player_setDirectionAndAddAccel;

    if (PASCAL_VERSION == 0) {
        csw->update = &csw_update;
        csw->fire = &csw_fire;
//        csw->setDirectionAndAddAccel = &player_setDirectionAndAddAccel;
    } else {
        csw->update = &csw_updatePV;
        csw->fire = &csw_firePV;
        csw->setDirectionAndAddAccel = &csw_setDirectionPV;
    }
    cswArr[1] = csw;
}

void csw_update(CSW * csw) {
    
}

void player_update(CSW * csw) {
    csw->inertia(csw);
}

double csw_getDirSum(CSW * csw) {
    return csw->inertiaDirections[0] +
        csw->inertiaDirections[1] +
        csw->inertiaDirections[2] +
        csw->inertiaDirections[3];
}

void csw_draw(CSW * csw) {
    if (PASCAL_VERSION == 0) {
        graphics_RenderLoadedTexture(csw->texture, 300+csw->x, 200+csw->y, 20, 20);
    } else {
        graphics_RenderLoadedTexture(csw->texture, 20 * csw->x + 20, 20 * csw->y + 20, 20, 20);
    }
}

void player_draw(CSW * csw) {
    if (PASCAL_VERSION == 0) {
        graphics_RenderLoadedTexture(csw->texture, 300+csw->x, 200+csw->y, 20, 20);
    } else {
        graphics_RenderLoadedTexture(csw->texture, 20 * csw->x + 20, 20 * csw->y + 20, 20, 20);
    }
}

int *base_getVXY(int d) {
    //int result[2];
    int *result = malloc(2);
    result[0] = 0; result[1] = 0;
    if (d == 0) {
        result[0] = 1; result[1] = 0;
    }
    if (d == 1) {
        result[0] = 0; result[1] = 1;
    }
    if (d == 2) {
        result[0] = -1; result[1] = 0;
    }
    if (d == 3) {
        result[0] = 0; result[1] = -1;
    }
    return result;
}

void csw_move(CSW * csw, int d) {
    int *nvxy = base_getVXY(d);
    double acceleration = csw_CSWSPEED + csw->inertiaDirections[d];
    // printf("nvxy = { %d, %d }\n", nvxy[0], nvxy[1]);
    
    double ux = nvxy[0] * acceleration;
    double uy = nvxy[1] * acceleration;
    
    // TODO: get ship dimensions by current direction
    int width = 20-1, height = 20-1;
    
    //if (csw.x + ux
    
    csw->x = csw->x + (int)ux;
    csw->y = csw->y + (int)uy;
    
    free(nvxy);
}

void csw_inertia(CSW * csw) {
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
