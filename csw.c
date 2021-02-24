#include "includes.h"
#include "csw.h"

#define csw_MAXIMUM_ACCELERATION 20
#define csw_CSWSPEED 0

void csw_move(struct CSWs * csw, int d);
void player_draw(struct CSWs * csw);
void csw_inertia(struct CSWs * csw);
CSW * csw_GetCSW(int x, int y);

void bullet_draw(BulletPV * bullet);
void bullet_fly(BulletPV * bullet);
void bullet_init(BulletPV * bullet, int x, int y, int d, bool isFire);

int *base_getVXY(int d);

//SDL_Color graphics_editor_colors[COLORMAX];

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
    csw->accelPV = unused;
}

CSW * csw_GetCSW(int x, int y) {
    int cnt = 0;
    while(cnt < 2) {
        if (cswArr[cnt]->x == x && cswArr[cnt]->y == y) {
            return cswArr[cnt];
        }
        cnt++;
    }
    return NULL;
}

void csw_updatePV(CSW * csw) {
    printf("\ncsw->life in update = %d", csw->life);

    if (csw->bullet.isFire) {
        bullet_fly(&csw->bullet);
    }
    if (csw->life <= 0) {
        csw->life = 0;
    } else {
        //if (csw->iam == USER) {
            //printf("\niam=%d, d=%d", csw->iam, csw->d);
            int *nvxy = base_getVXY(csw->d);
            int vx = nvxy[0] * csw->accelPV;
            int vy = nvxy[1] * csw->accelPV;
            if ((csw->x + vx) > 20 || (csw->x + vx < 1)) {
                vx = 0;
            }
            if ((csw->y + vy) > 20 || (csw->y + vy < 1)) {
                vy = 0;
            }
            if(!(vx == 0 && vy == 0)) {
                if (csw_GetCSW(csw->x + vx, csw->y + vy) != NULL) {
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

void csw_fire(CSW * csw) {
    if (PASCAL_VERSION == 1) {
        //printf("\ncsw->life = %d", csw->life);
        if (csw->d != 5 && csw->life > 0 && csw->bullet.isFire == false) {
            //printf("\nfire!");
            bullet_init(&csw->bullet, csw->x, csw->y, csw->d, true);
        }
    }
}

void bullet_init(BulletPV * bullet, int x, int y, int d, bool isFire) {
    bullet->x = x;
    bullet->y = y;
    bullet->d = d;
    bullet->isFire = isFire;
}

void bullet_fly(BulletPV * bullet) {
    int vx;
    int vy;
    int vx1;
    int vy1;

    if (bullet->isFire == true) {
        int *nvxy = base_getVXY(bullet->d);
        int vx = nvxy[0];
        int vy = nvxy[1];
        bullet->x = bullet->x + vx;
        bullet->y = bullet->y + vy;

        bullet_draw(bullet);

        if (bullet->parent == USER) {
            printf("\nuuuu bullet fly!");
            printf("\nuuuu bullet->d = %d", bullet->d);
            printf("\nuuuu vx = %d vy = %d", vx, vy);
            printf("\nuuuu bullet->x = %d bullet->y = %d", bullet->x, bullet->y);
        }
        
        if ((bullet->x + vx) > 20 || (bullet->x + vx < 1)) {
            vx = 0;
            bullet->isFire = false;
        }
        if ((bullet->y + vy) > 20 || (bullet->y + vy < 1)) {
            vy = 0;
            bullet->isFire = false;
        }
        if(!(vx == 0 && vy == 0)) {
            CSW * foundCSW = csw_GetCSW(bullet->x + vx, bullet->y + vy);
            if (foundCSW != NULL && foundCSW->life > 0) {
                vx = 0;
                vy = 0;
                foundCSW->life--;
                bullet->isFire = false;
            }
        }
    }
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
    csw->fire = &csw_fire;
    csw->move = &csw_move;
    csw->setDirectionAndAddAccel = &player_setDirectionAndAddAccel;

    bullet_init(&csw->bullet, 0, 0, 5, false);
    csw->bullet.parent = csw->iam;
    
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
    csw->lastActionTime = 0;
    csw->d = 5;
    csw->x = x;
    csw->y = y;
    csw->life = 100;
    csw->inertiaTimerIsRunning = 0;
    csw->texture = graphics_LoadFromPNG("images/csw-mt5.png");
    
    csw->draw = &csw_draw;
    csw->fire = &csw_fire;
    // csw.setDirectionAndAddAccel = &player_setDirectionAndAddAccel;

    bullet_init(&csw->bullet, 0, 0, 5, false);
    csw->bullet.parent = csw->iam;
    
    if (PASCAL_VERSION == 0) {
        csw->update = &csw_update;
//        csw->setDirectionAndAddAccel = &player_setDirectionAndAddAccel;
    } else {
        csw->update = &csw_updatePV;
        //csw->fire = &csw_firePV;
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

void bullet_draw(BulletPV * bullet) {
    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Point points[1] = {
        {20 * bullet->x + 20, 20 * bullet->y + 20},     // {Vertical up}
    };

    graphics_PutPixels(points, color, 1);
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
