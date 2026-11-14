/* class: HUD widget (HUD widget vtable entries: 9 focus change, 10 Show 0x1D98B0, 11 Hide 0x1D9910, 12 find the screen object
 * 0x1DA770, 13 reset 0x1DA7B0, 14 the state): the base reset (entry 13; ResetHudWidgets 0x1D9408 calls it) - no screen object, then
 * no state (0x1DA7D0). */
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

void func_001DA7D0(HUDWIDGET *pwidget);

void func_001DA7B0(HUDWIDGET *pwidget)
{
    pwidget->ploScreen = 0;
    func_001DA7D0(pwidget);
}
