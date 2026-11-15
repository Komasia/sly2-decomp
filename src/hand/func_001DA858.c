/* UpdateShopStick (SafeHouse shop.cpp): the stick picks a direction for a HUD menu widget: with no direction, a
 * stick pushed past 0.8 gives one of 8 directions (its angle in eighths, vt slot 14: set the direction); a held
 * direction is released (-1) once the stick drops below 0.5. */
#include "vtbl.h"
typedef struct JOY { char pad[0x103C]; float x; float y; float uMagnitude; } JOY;   /* the left stick */
typedef struct SHOP {                 /* field: SafeHouse port (shop.cpp) */
    /* 0x00 */ char pad[0xC];
    /* 0x0c */ VTENT *vt;
    /* 0x10 */ JOY *pjoy;             /* the pad while the widget has the focus */
    /* 0x14 */ char pad14[0x28 - 0x14];
    /* 0x28 */ int dir;               /* the stick's direction (-1: none) */
} SHOP;
float atan2f(float y, float x);

// name: SafeHouse port (UpdateShopStick)
void UpdateShopStick__FP4SHOP(SHOP *pshop)
{
    JOY *pjoy = pshop->pjoy;
    int dir;
    float uMagnitude;
    if (pjoy == 0)
        return;
    dir = pshop->dir;
    uMagnitude = pjoy->uMagnitude;
    if (dir == -1) {
        if (0.8f < uMagnitude) {
            int dirNew = (int)(atan2f(pjoy->y, pjoy->x) * 1.2732395f + 8.5f);   /* 4 / pi: eighths of a turn */
            ((void (*)(void *, int))pshop->vt[14].pfn)(VT_THIS(pshop, &pshop->vt[14]), dirNew % 8);
        }
    } else if (uMagnitude < 0.5f) {
        ((void (*)(void *, int))pshop->vt[14].pfn)(VT_THIS(pshop, &pshop->vt[14]), -1);
    }
}
