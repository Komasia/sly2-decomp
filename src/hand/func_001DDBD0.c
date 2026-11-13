/* class: a HUD widget (vtable around 0x2D81BC; SafeHouse frontend.cpp: Europe's language menu): a new state +0x28,
 * with the real time it changed at +0x2C. */
#include "clock.h"
struct WIDGET {
    /* 0x00 */ char pad0[0x28];
    /* 0x28 */ int state;
    /* 0x2c */ float tState;   /* g_clock.tReal at the change */
};

void func_001DDBD0(struct WIDGET *pwidget, int state)
{
    if (state != pwidget->state) {
        pwidget->state = state;
        pwidget->tState = g_clock.tReal;
    }
}
