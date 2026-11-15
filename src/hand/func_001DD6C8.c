/* class: the timed message HUD widget D_003DA4F0: show it - when it has a screen object, the widget's Show (vtable
 * entry 10) and the screen object shown (its vtable entry 49, -1: the default). */
#include "vtbl.h"
struct O { int a, b, c; VTENT *vt; };
struct HUDWIDGET {
    /* 0x00 */ int a, b, c;
    /* 0x0c */ VTENT *vt;
    /* 0x10 */ char pad10[0x14];
    /* 0x24 */ struct O *pscreen;
};
void func_001DD6C8(struct HUDWIDGET *pwidget) {
    if (pwidget->pscreen) {
        {
            VTENT *pvtent = &pwidget->vt[10];
            ((void (*)(void *))pvtent->pfn)(VT_THIS(pwidget, pvtent));
        }
        {
            struct O *pscreen = pwidget->pscreen;
            VTENT *pvtent = &pscreen->vt[49];
            ((void (*)(void *, int))pvtent->pfn)(VT_THIS(pscreen, pvtent), -1);
        }
    }
}
