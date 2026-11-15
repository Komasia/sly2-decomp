/* class: the HUD's widget list D_003D9E70 (SafeHouse hudwidget.h): bring the focus up to date - the focus goes to the
 * first widget of the list. The widget losing it gets no pad and vtable entry 9 (0, the new one); the one gaining it
 * gets the pad g_joy and entry 9 (1, the old one). */
#include "vtbl.h"
struct HUDWIDGET {
    /* 0x00 */ int a, b, c;
    /* 0x0c */ VTENT *vt;
    /* 0x10 */ void *pjoy;            /* the pad while it has the focus */
};
struct HUDLIST {
    /* 0x00 */ struct HUDWIDGET *pwidgetFirst;   /* the list's head */
    /* 0x04 */ int a, b;
    /* 0x0c */ struct HUDWIDGET *pwidgetFocus;
};
extern char g_joy[];

void func_001D95B8(struct HUDLIST *plist)
{
    struct HUDWIDGET *pwidget = plist->pwidgetFirst;
    struct HUDWIDGET *pwidgetOld;
    if (pwidget == plist->pwidgetFocus)
        return;
    if (plist->pwidgetFocus) {
        plist->pwidgetFocus->pjoy = 0;
        {
            struct HUDWIDGET *pwidgetLose = plist->pwidgetFocus;
            VTENT *pvtent = &pwidgetLose->vt[9];
            ((void (*)(void *, int, struct HUDWIDGET *))pvtent->pfn)(VT_THIS(pwidgetLose, pvtent), 0, pwidget);
        }
    }
    pwidgetOld = plist->pwidgetFocus;
    plist->pwidgetFocus = pwidget;
    if (pwidget) {
        VTENT *pvtent = &pwidget->vt[9];
        pwidget->pjoy = g_joy;
        ((void (*)(void *, int, struct HUDWIDGET *))pvtent->pfn)(VT_THIS(pwidget, pvtent), 1, pwidgetOld);
    }
}
