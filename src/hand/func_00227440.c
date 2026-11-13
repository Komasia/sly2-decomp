/* class: VOLUME, the camera volumes (class 5; SafeHouse cmworld.cpp: 0x14E078 / 0x2273F0 / 0x227440): a new state
 * +0x110, with the time it changed at +0x114. */
#include "clock.h"
struct VOLUME {
    /* 0x000 */ char pad0[0x110];
    /* 0x110 */ int state;
    /* 0x114 */ float tState;   /* g_clock.t at the change */
};

void func_00227440(struct VOLUME *pvolume, int state)
{
    if (state != pvolume->state) {
        pvolume->state = state;
        pvolume->tState = g_clock.t;
    }
}
