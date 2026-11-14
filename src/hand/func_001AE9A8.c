/* class: the menu HUD widget D_003D9ED0 (vtable 0x2D37D0: ShowMenuWidget is its entry 10): its focus change (vtable entry 9; the
 * base 0x1D98A8 is empty) - on gaining the focus the pad's pending presses are dropped (0x187E78). */
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

void func_001D98A8(HUDWIDGET *pwidget, int fFocus);
void func_00187E78(void *pjoy);

void func_001AE9A8(HUDWIDGET *pwidget, int fFocus)
{
    func_001D98A8(pwidget, fFocus);
    if (fFocus != 0) {
        func_00187E78(pwidget->pjoy);
    }
}
