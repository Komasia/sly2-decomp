/* UpdateBooty (the booty's vt slot 16): the SO's update; then a thrown booty (state 5) goes back to its stand after
 * 5 s, and a carried one (state 4) of a timed record (+0xC) is dropped by its carrier when the HUD timer
 * (D_003E1BFC) runs out. Layout: SafeHouse port (booty.cpp BOOTY, BOOTYREC). */
#include "clock.h"

struct ACTOR;
struct BOOTYREC {
    /* 0x0 */ char pad0[0xc];
    /* 0xc */ int fC;                    /* field: SafeHouse port - timed */
};
struct BOOTY {
    /* 0x000 */ char pad0[0x158];
    /* 0x158 */ struct BOOTYREC *prec;   /* the current record */
    /* 0x15c */ struct LO *pstand;       /* field: SafeHouse port */
    /* 0x160 */ struct ACTOR *pcarrier;  /* field: SafeHouse port */
    /* 0x164 */ char pad164[0x184 - 0x164];
    /* 0x184 */ int state;               /* field: SafeHouse port */
    /* 0x188 */ float t;                 /* field: SafeHouse port - the state's start */
};
extern float D_003E1BFC;   /* SafeHouse: THudTimerEnd */
void UpdateSo__FP2SOf(struct BOOTY *pbooty, float dt);
void ReturnThrownBooty__FP2LO(struct BOOTY *pbooty, int n);
void DropActorBooty__FP5ACTORii(struct ACTOR *pactor);

// name: SafeHouse port (UpdateBooty)
void UpdateBooty__FP2LO(struct BOOTY *pbooty, float dt)
{
    UpdateSo__FP2SOf(pbooty, dt);
    switch (pbooty->state) {
    case 5:
        if (g_clock.t - pbooty->t >= 5.0f) {
            ReturnThrownBooty__FP2LO(pbooty, 0);
            return;
        }
        return;
    case 4:
        if (pbooty->prec->fC && g_clock.t >= D_003E1BFC)
            DropActorBooty__FP5ACTORii(pbooty->pcarrier);
        break;
    }
}
