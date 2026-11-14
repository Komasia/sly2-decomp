/* class: the gadget menu HUD widget D_003DA0F0 (a SELECTOR, vtable 0x2D8568; its constructor 0x1DAA08 and reset
 * 0x1DAA48 call it):
 * no selection (+0x40 -1), its time the real time. */
#include "clock.h"
typedef struct LO LO;
typedef struct HUDWIDGET {      /* a HUD widget (SafeHouse hudwidget.h; module 0x1D93D8..0x1DFAD8) */
    /* 0x00 */ void *apvBasic[3];
    /* 0x0c */ void *pvt;
    /* 0x10 */ void *pjoy;           /* the pad while the widget has the focus (0x1D95B8) */
    /* 0x14 */ char pad14[0xc];
    /* 0x20 */ int oidScreen;        /* its screen object */
    /* 0x24 */ LO *ploScreen;
    /* 0x28 */ int state;
    /* 0x2c */ float tState;         /* g_clock.tReal at the state change */
} HUDWIDGET;
typedef struct SELECTOR {
    /* 0x00 */ HUDWIDGET widget;
    /* 0x30 */ char pad30[0x10];
    /* 0x40 */ int isel;
    /* 0x44 */ float tSel;
} SELECTOR;

void func_001DAA78(SELECTOR *psel)
{
    psel->isel = -1;
    psel->tSel = g_clock.tReal;
}
