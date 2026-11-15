/* func_001DE008 (0x1DE008): g++ static initialisation / destruction of the HUD widget translation unit
 * (__static_initialization_and_destruction_0, module 0x1D93D8..0x1DFAD8). With fInitialize it constructs the unit's
 * globals - the widget list D_003D9E70, the gauge D_003D9E80, the menu D_003D9ED0, the prompt D_003DA0C0, the two
 * SHOP-class widgets D_003DA0F0 / D_003DA150 (gadget menu / shop), the job help D_003DA3C0 and the timed message / title widgets D_003DA4F0 /
 * D_003DA530 - and the slot heaps of the unit's CStructTypeFactory<T>::s_slotheap statics (each guarded by its g++
 * sentry counter, so a heap shared with other units is built only once); otherwise it destroys the widgets in
 * reverse order (func_00258348 with __in_chrg = 2: not deleting). */
#include "slotheap.h"

/* the first words of a widget object: the base constructor is inlined for these three */
typedef struct WIDGETHEAD {
    /* 0x0 */ int unk_0x0;
    /* 0x4 */ int unk_0x4;
    /* 0x8 */ int unk_0x8;
    /* 0xc */ void *pvt;
} WIDGETHEAD;

extern char D_003D9E70[];                  /* the HUD widget list (DL) */
extern WIDGETHEAD D_003D9E80;              /* gauge */
extern WIDGETHEAD D_003D9ED0;              /* menu */
extern WIDGETHEAD D_003DA0C0;              /* prompt */
extern char D_002D8668[], D_002D37D0[], D_002CA490[];   /* their vtables */
extern char D_003DA0F0[], D_003DA150[];    /* SHOP-class widgets */
extern char D_003DA3C0[];                  /* job help */
extern char D_003DA4F0[], D_003DA530[];    /* timed message, title */
extern int D_002DD2E0, D_002DD2E4, D_002DD2E8, D_002DD2EC, D_002DD2F0, D_002DD2F4;   /* slot heap sentries */
extern SLOTHEAP D_004520A8, D_004520D0, D_004520F8, D_00452120, D_00452148, D_00452170;
void *func_001D93D8(void *); /* constructor: returns this */
void *func_001DAA08(void *); /* constructor: returns this */
void *func_001DB7A8(void *); /* constructor: returns this */
void *func_001DCC58(void *); /* constructor: returns this */
void *func_001DD648(void *); /* constructor: returns this */
void *func_001DD7D8(void *); /* constructor: returns this */
void func_00258348(void *, int);           /* destructor (this, __in_chrg) */

static inline void InitWidgetHead(WIDGETHEAD *pwidget, void *pvt)
{
    pwidget->unk_0x0 = 0;
    pwidget->unk_0x4 = 0;
    pwidget->pvt = pvt;
}

void func_001DE008(int fInitialize, int nPriority)
{
    if (nPriority == 0xFFFF) {
        if (fInitialize) {
            func_001D93D8(D_003D9E70);
            InitWidgetHead(&D_003D9E80, D_002D8668);
            InitWidgetHead(&D_003D9ED0, D_002D37D0);
            InitWidgetHead(&D_003DA0C0, D_002CA490);
            func_001DAA08(D_003DA0F0);
            func_001DB7A8(D_003DA150);
            func_001DCC58(D_003DA3C0);
            func_001DD648(D_003DA4F0);
            func_001DD7D8(D_003DA530);
            if (++D_002DD2E0 == 1)
                func_0011CCA8(&D_004520A8, 0x14, 0x2000, 0x10);
            if (++D_002DD2E4 == 1)
                func_0011CCA8(&D_004520D0, 0x18, 0x800, 0x10);
            if (++D_002DD2E8 == 1)
                func_0011CCA8(&D_004520F8, 0x28, 0x200, 0x10);
            if (++D_002DD2EC == 1)
                func_0011CCA8(&D_00452120, 0x1C, 0x800, 0x10);
            if (++D_002DD2F0 == 1)
                func_0011CCA8(&D_00452148, 0xC, 0xC8, 0x10);
            if (++D_002DD2F4 == 1)
                func_0011CCA8(&D_00452170, 0x14, 0x100, 0x10);
        } else {
            func_00258348(D_003DA530, 2);
            func_00258348(D_003DA4F0, 2);
            func_00258348(D_003DA3C0, 2);
            func_00258348(D_003DA150, 2);
            func_00258348(D_003DA0F0, 2);
            func_00258348(&D_003DA0C0, 2);
            func_00258348(&D_003D9ED0, 2);
            func_00258348(&D_003D9E80, 2);
        }
    }
}
