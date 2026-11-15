/* FUseBootyStand: an actor uses a booty stand: the actor's booty goes onto the stand (state 3, flying to it) and / or
 * the stand's booty to the actor (state 2), the move saved; refused with a task event 0x32 when the stand has +0x190 set
 * or the booty's record does not fit the stand (+0x188), and with a message / sound when the stand's booty
 * is not takeable now (D_003E0F9C and its record's +0x10 clear). Layout: SafeHouse port (booty.cpp). */
#include "cid.h"
struct BOOTYREC { int id; int x4; int x8; int fC; int f10; int nStands; };   /* field: SafeHouse port (booty.cpp: +0x14 the stands it may be put on) */
struct BOOTY { char pad[0x158]; struct BOOTYREC *prec; void *pstand; void *pcarrier; };   /* field: SafeHouse port */
struct ACTOR { char pad[0x11A8]; struct BOOTY *pbooty; };   /* the booty the actor carries */
struct STAND { char pad[0x188]; int nStands; int x18C; int f190; struct BOOTY *pbooty; };   /* field: SafeHouse port (booty.cpp) */
extern int D_003E0F9C;
extern char D_003DA0C0[];
extern char g_game[];
int FIsBasicDerivedFrom__FP5BASIC3CID(struct ACTOR *pactor, int k);
void func_001DA4B8(void *pv, int n, float g);
void *PsndNewPlain__Fi(int n);
void SetSource__4CSndPv(void *pv, int n);
void BroadcastTaskEvent__FP2SWiP2LO(void *pv, int n, struct STAND *pstand);
void SaveBootyMove__FP5ACTORiP2LO(struct ACTOR *pactor, int n, struct STAND *pstand);
void SetBootyState__FP2LOi(struct BOOTY *pa, int n);
void UseObjectBase__FP2LOi(struct STAND *pstand, struct ACTOR *pactor);
// name: SafeHouse port (FUseBootyStand)
void FUseBootyStand__FP2LOP5ACTOR(struct STAND *pstand, struct ACTOR *pactor)
{
    struct BOOTY *pbootyActor, *pbootyStand;
    if (!FIsBasicDerivedFrom__FP5BASIC3CID(pactor, CID_ACTOR))
        return;
    pbootyActor = pactor->pbooty;
    pbootyStand = pstand->pbooty;
    if (!pbootyActor && !pbootyStand)
        return;
    if (pbootyStand && D_003E0F9C && !pbootyStand->prec->f10) {
        func_001DA4B8(D_003DA0C0, 0x124, 15.0f);
        SetSource__4CSndPv(PsndNewPlain__Fi(0x36), 0);
        return;
    }
    if (pstand->f190 || (pbootyActor && pbootyActor->prec->nStands != pstand->nStands)) {
        BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x32, pstand);
        return;
    }
    if (pstand->pbooty)
        SetSource__4CSndPv(PsndNewPlain__Fi(0x27), 0);
    SaveBootyMove__FP5ACTORiP2LO(pactor, 0, pstand);
    if (pactor->pbooty && pstand->pbooty) {
        pactor->pbooty->pstand = pstand;
        SetBootyState__FP2LOi(pactor->pbooty, 3);
        pstand->pbooty->pcarrier = pactor;
        SetBootyState__FP2LOi(pstand->pbooty, 2);
    } else if (pactor->pbooty) {
        pactor->pbooty->pstand = pstand;
        SetBootyState__FP2LOi(pactor->pbooty, 3);
    } else {
        pstand->pbooty->pcarrier = pactor;
        SetBootyState__FP2LOi(pstand->pbooty, 2);
    }
    UseObjectBase__FP2LOi(pstand, pactor);
}
