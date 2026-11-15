/* SetGadgetMenu (SafeHouse shop.cpp): open the gadget menu for character ichar (0..2) or close it (-1). Opening
 * stops the game clock, pauses the game and shows the widget (vtable entry 10); closing hides the screen object
 * and the widget, forgets the entries and resumes. An open menu takes its character's gadget list and screen
 * object (0x375 + ichar), plays its open animation and selects the owned gadget nearest the top left (smallest
 * x + y). */
#include "vtbl.h"
typedef struct { char pad0[0xC]; VTENT *vt; } SUB;
#define GRFGADGET_Owned 4             /* UpdateGadgetFlags: func_001DAEA8 */
#define OID_SCREENGADGETS 0x375       /* + ichar: the three characters' gadget screens */
#define WID_GADGETMENUOPEN 0x318
typedef struct GADGETENT {            /* field: SafeHouse port (shop.cpp GADGETENT) */
    /* 0x00 */ int key;
    /* 0x04 */ int idOpen;
    /* 0x08 */ int idOwned;
    /* 0x0c */ int idSel;
    /* 0x10 */ int idCur;
    /* 0x14 */ float x;
    /* 0x18 */ float y;
    /* 0x1c */ int grf;
} GADGETENT;
typedef struct GADGETMENU {           /* field: SafeHouse port (shop.cpp GADGETMENU) */
    /* 0x00 */ char pad0[0xC];
    /* 0x0c */ VTENT *vt;
    /* 0x10 */ char pad10[0x20 - 0x10];
    /* 0x20 */ int oidScreen;
    /* 0x24 */ SUB *pscreen;
    /* 0x28 */ char pad28[0x40 - 0x28];
    /* 0x40 */ int ichar;             /* -1: closed */
    /* 0x44 */ float tChar;
    /* 0x48 */ int key;
    /* 0x4c */ int cent;
    /* 0x50 */ GADGETENT *aent;
} GADGETMENU;
#include "clock.h"
extern char g_sw[];
extern GADGETENT D_002C2DE8[], D_002C3028[], D_002C3148[];
extern float D_002A79CC;              /* a large value */
void SetClockFactor__FP5CLOCKif(struct CLOCK *, float, int);
void PauseGame__FP9GAMEPAUSEi(void *, int);
void ResumeGame__FP9GAMEPAUSEi(void *, int);
void SelectGadget__FPvi(GADGETMENU *, int);
void SetShopMsg__FP4SHOPii(GADGETMENU *, int, int);
void UpdateGadgetFlags__FPv(GADGETMENU *);
SUB *PloFindSwNearest__FP2LO3OIDii(void *, int, int, int);
void SetGadgetMenu__FPvi(GADGETMENU *pmenu, int ichar);
#define VCALL(o, n) ((void (*)(void *))(o)->vt[n].pfn)(VT_THIS((o), &(o)->vt[n]))
// name: SafeHouse port (SetGadgetMenu)
void SetGadgetMenu__FPvi(GADGETMENU *pmenu, int ichar)
{
    if (ichar == pmenu->ichar)
        return;
    if (pmenu->ichar == -1) {
        SetClockFactor__FP5CLOCKif(&g_clock, 0.0f, 0);
        PauseGame__FP9GAMEPAUSEi(g_sw, 0);
        VCALL(pmenu, 10);
    }
    SelectGadget__FPvi(pmenu, -1);
    pmenu->ichar = ichar;
    pmenu->tChar = g_clock.tReal;
    switch (ichar) {
    case -1: {
        int i;
        if (pmenu->pscreen)
            VCALL(pmenu->pscreen, 50);
        for (i = 0; i < pmenu->cent; i++)
            pmenu->aent[i].idCur = -1;
        pmenu->cent = 0;
        pmenu->aent = 0;
        SetClockFactor__FP5CLOCKif(&g_clock, 1.0f, 0);
        ResumeGame__FP9GAMEPAUSEi(g_sw, 0);
        VCALL(pmenu, 11);
        SetShopMsg__FP4SHOPii(pmenu, -1, -1);
        pmenu->pscreen = 0;
        pmenu->oidScreen = -1;
        break;
    }
    case 0:
        pmenu->oidScreen = OID_SCREENGADGETS;
        pmenu->cent = 0x12;
        pmenu->aent = D_002C2DE8;
        break;
    case 1:
        pmenu->oidScreen = OID_SCREENGADGETS + 1;
        pmenu->cent = 9;
        pmenu->aent = D_002C3028;
        break;
    case 2:
        pmenu->oidScreen = OID_SCREENGADGETS + 2;
        pmenu->cent = 8;
        pmenu->aent = D_002C3148;
        break;
    }
    if (pmenu->ichar != -1) {
        SUB *pscreen;
        UpdateGadgetFlags__FPv(pmenu);
        pscreen = PloFindSwNearest__FP2LO3OIDii(g_sw, 5, pmenu->oidScreen, 0);
        pmenu->pscreen = pscreen;
        if (!pscreen) {
            SetGadgetMenu__FPvi(pmenu, -1);
        } else {
            float gBest;
            int key;
            int i;
            ((void (*)(void *, int))pscreen->vt[49].pfn)(VT_THIS(pscreen, &pscreen->vt[49]), WID_GADGETMENUOPEN);
            gBest = D_002A79CC;
            key = -1;
            for (i = 0; i < pmenu->cent; i++) {
                GADGETENT *pent = &pmenu->aent[i];
                if (pent->grf & GRFGADGET_Owned) {
                    float g = pent->x + pent->y;
                    if (g < gBest) {
                        key = pent->key;
                        gBest = g;
                    }
                }
            }
            SelectGadget__FPvi(pmenu, key);
        }
    }
}
