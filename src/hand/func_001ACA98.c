/* class: the memory card prompt D_002E6550 (SafeHouse menu.h "the card dialog, on screen object 0x52C"; built by
 * the unit's static initialiser 0x1ADF98): its constructor - the HUD widget base 0x1DA728, the vtable 0x2D3750,
 * screen object 0x52C, no message (+0x40 -1), then 0x1DA7D0 (no state). */
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
typedef struct CARDPROMPT {
    /* 0x00 */ HUDWIDGET widget;
    /* 0x30 */ char pad30[0x10];
    /* 0x40 */ int msg;              /* the message shown (0x1ACB58) */
} CARDPROMPT;

HUDWIDGET *func_001DA728(HUDWIDGET *pwidget);
void func_001DA7D0(HUDWIDGET *pwidget);
extern char D_002D3750[];   /* its vtable */

CARDPROMPT *func_001ACA98(CARDPROMPT *pprompt)
{
    func_001DA728(&pprompt->widget);
    pprompt->widget.pvt = D_002D3750;
    pprompt->widget.oidScreen = 0x52C;
    pprompt->msg = -1;
    func_001DA7D0(&pprompt->widget);
    return pprompt;
}
