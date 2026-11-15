/* SetGaugeState (SafeHouse hudwidget.cpp, orig 0x1D9B60): change the gauge's state and show the state's animation;
 * Idle shows both meters - the power meter only when the player owns a gadget that uses power. */
#include "vtbl.h"
#include "h3_hud.h"
typedef struct { char pad0[0xC]; VTENT *vt; } SUB;
typedef struct { int gadget; int pad[7]; } GADGETSLOT;     /* a player class's gadget list entry */
typedef struct { int use, kind, cost, power; int pad[4]; } ITEM;   /* the item table (SafeHouse shop.cpp / gadget.cpp) */
typedef struct GAUGE {                /* field: SafeHouse port (hudwidget.cpp GAUGE) */
    /* 0x00 */ char pad0[0x20];
    /* 0x20 */ float hShown;
    /* 0x24 */ char pad24[0x28 - 0x24];
    /* 0x28 */ float gShown;
    /* 0x2c */ char pad2c[0x30 - 0x2C];
    /* 0x30 */ int state;             /* GAUGES */
    /* 0x34 */ void *pplayer;
    /* 0x38 */ SUB *pscreen;
    /* 0x3c */ int idIdle;            /* the screen object's animations */
    /* 0x40 */ int idHit;
    /* 0x44 */ int idHide;
    /* 0x48 */ int idBack;
    /* 0x4c */ int idLow;
} GAUGE;
extern GADGETSLOT D_002C2DE8[], D_002C3028[], D_002C3148[];   /* the gadgets of classes 0x35, 0x37, 0x36 */
extern ITEM D_002BCD00[];
int FIsBasicDerivedFrom__FP5BASIC3CID(void *, int);
int FPowerupOwned__Fi(int item);           /* the item is acquired */
void SelectScreenObjPart__FP2LOi(SUB *pscreen, int wid);          /* SafeHouse SelectScreenObjPart */
void ResetScreenObjPart__FP2LOi(SUB *pscreen, int wid);          /* SafeHouse ResetScreenObjPart */
void SetScreenObjFraction__FP2LOif(SUB *pscreen, int wid, float g); /* SafeHouse SetScreenObjFraction */
/* vt slot 49 of the screen object: show an animation (SafeHouse ShowScreenObj) */
#define VCALL1(o, n, a) ((void (*)(void *, int))(o)->vt[n].pfn)(VT_THIS((o), &(o)->vt[n]), a)
// name: SafeHouse port (SetGaugeState)
void SetGaugeState__FP5GAUGEi(GAUGE *pgauge, int state)
{
    int stateOld = pgauge->state;
    if (stateOld == state)
        return;
    if (!pgauge->pscreen)
        return;
    if (stateOld == GAUGES_Hit || stateOld == GAUGES_State6)
        VCALL1(pgauge->pscreen, 49, pgauge->idIdle);
    pgauge->state = state;
    switch (state) {
    case GAUGES_Hidden:
    case GAUGES_Back:
        VCALL1(pgauge->pscreen, 49, pgauge->idHide);
        break;
    case GAUGES_Idle: {
        int cslot = 0;
        GADGETSLOT *aslot = 0;
        int fPower;
        int islot;
        VCALL1(pgauge->pscreen, 49, pgauge->idIdle);
        SelectScreenObjPart__FP2LOi(pgauge->pscreen, WID_HEALTHMETER);
        SetScreenObjFraction__FP2LOif(pgauge->pscreen, WID_HEALTHMETER, 1.0f - pgauge->hShown);
        if (FIsBasicDerivedFrom__FP5BASIC3CID(pgauge->pplayer, 0x35)) {
            cslot = 0x12;
            aslot = D_002C2DE8;
        } else if (FIsBasicDerivedFrom__FP5BASIC3CID(pgauge->pplayer, 0x37)) {
            cslot = 9;
            aslot = D_002C3028;
        } else if (FIsBasicDerivedFrom__FP5BASIC3CID(pgauge->pplayer, 0x36)) {
            cslot = 8;
            aslot = D_002C3148;
        }
        fPower = 0;
        for (islot = 0; islot < cslot; islot++) {
            int gadget = aslot[islot].gadget;
            if (FPowerupOwned__Fi(gadget)) {
                ITEM item = D_002BCD00[gadget];
                if (item.power > 0) {
                    fPower = 1;
                    break;
                }
            }
        }
        if (fPower) {
            SelectScreenObjPart__FP2LOi(pgauge->pscreen, WID_POWERMETER);
            SetScreenObjFraction__FP2LOif(pgauge->pscreen, WID_POWERMETER, 1.0f - pgauge->gShown);
        } else {
            ResetScreenObjPart__FP2LOi(pgauge->pscreen, WID_POWERMETER);
        }
        break;
    }
    case GAUGES_Hit:
        VCALL1(pgauge->pscreen, 49, pgauge->idHit);
        break;
    case GAUGES_State6:
        VCALL1(pgauge->pscreen, 49, pgauge->idBack);
        break;
    case GAUGES_State7:
        VCALL1(pgauge->pscreen, 49, pgauge->idLow);
        break;
    }
}
