/* class: the Job Help HUD widget D_003DA3C0 (vtable 0x2D8468: UpdateJobHelp is its entry 7; built by 0x1DCC58): its reset (vtable entry 13) - the
 * base 0x1DA7B0, then its own fields (0x1DCD08). */
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

void func_001DA7B0(HUDWIDGET *pwidget);
void func_001DCD08(HUDWIDGET *pwidget);

void func_001DCCD8(HUDWIDGET *pwidget)
{
    func_001DA7B0(pwidget);
    func_001DCD08(pwidget);
}
