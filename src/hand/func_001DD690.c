/* class: the timed message HUD widget D_003DA4F0 (vtable 0x2D83E8, screen object 0x52D; called by InitHudWidgets): its screen object found (vtable entry 12: the base
 * 0x1DA770) and made visible (+0xB0). */
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
typedef struct SCREENOBJ { char pad0[0xb0]; int fShown; } SCREENOBJ;

void func_001DA770(HUDWIDGET *pwidget);

void func_001DD690(HUDWIDGET *pwidget)
{
    SCREENOBJ *pscreen;

    func_001DA770(pwidget);
    pscreen = (SCREENOBJ *)pwidget->ploScreen;
    if (pscreen != 0) {
        pscreen->fShown = 1;
    }
}
