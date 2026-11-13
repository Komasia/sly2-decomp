/* SetDockState: a hack dock's state: 0 waiting, 1 docking (the ship (+0x1C8) gets the dock point (+0x1CC) and its
 * state 3), 2 done (the task event 0x39); leaving 1 with a ship lets it go (0x181728); then the state's segment
 * (+0x1D0, 0x10 bytes each; none for -1) played. Layout: SafeHouse port (hack.cpp HACKSO). */
#include "clock.h"

struct HACKSEG {
    /* 0x0 */ int oid;
    /* 0x4 */ void *paseg;
    /* 0x8 */ void *psm;
    /* 0xc */ int grfapl;
};
struct SHIP {
    /* 0x000 */ char pad0[0x294];
    /* 0x294 */ struct LO *ploDock;       /* field: SafeHouse port */
};
struct DOCK {
    /* 0x000 */ char pad0[0x1c0];
    /* 0x1c0 */ int state;                /* field: SafeHouse port */
    /* 0x1c4 */ float tState;             /* field: SafeHouse port */
    /* 0x1c8 */ struct SHIP *ploShooter;  /* field: SafeHouse port - the ship docking */
    /* 0x1cc */ struct LO *ploEnemyTarget;   /* field: SafeHouse port - the dock point */
    /* 0x1d0 */ struct HACKSEG aseg[3];   /* field: SafeHouse port */
};
extern char g_game[];
void func_00181728(struct DOCK *pdock);   /* SafeHouse: the ship let go */
void SetShipState__FP2LOi(struct SHIP *pship, int st);
void BroadcastTaskEvent__FP2SWiP2LO(void *pgame, int n, struct DOCK *pdock);
void PlayHackSeg__FP2LOP6HACKSO(struct DOCK *pdock, struct HACKSEG *pseg);

// name: SafeHouse port (SetDockState)
void SetDockState__FP2LOi(struct DOCK *pdock, int state)
{
    int stateOld = pdock->state;
    if (stateOld != state) {
        if (stateOld == 1 && pdock->ploShooter != 0)
            func_00181728(pdock);
        pdock->state = state;
        pdock->tState = g_clock.t;
        switch (state) {
        case 1:
            pdock->ploShooter->ploDock = pdock->ploEnemyTarget;
            SetShipState__FP2LOi(pdock->ploShooter, 3);
            break;
        case 2:
            BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x39, pdock);
            break;
        }
        PlayHackSeg__FP2LOP6HACKSO(pdock, state != -1 ? &pdock->aseg[state] : 0);
    }
}
