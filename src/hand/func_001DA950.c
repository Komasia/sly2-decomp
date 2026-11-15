/* SetShopMsg (SafeHouse shop.cpp): show a message on a HUD menu widget: kind -1 none, 0 a question (sound 0x29,
 * held: D_002A7984), else a message for D_002C3254 seconds of real time (sound 0x36); id is its text. */
#include "clock.h"
extern float D_002A7984, D_002C3254;
struct SHOP {                         /* field: SafeHouse port (shop.cpp) */
    /* 0x00 */ char pad0[0x30];
    /* 0x30 */ int msg;               /* -1 none, 0 a question, 1 a message */
    /* 0x34 */ float tMsg;            /* when it ends (real time) */
    /* 0x38 */ int idMsg;
};
void *PsndNewPlain__Fi(int sndid);
void SetSource__4CSndPv(void *psnd, int pvSource);

// name: SafeHouse port (SetShopMsg)
void SetShopMsg__FP4SHOPii(struct SHOP *pshop, int msg, int idMsg)
{
    pshop->idMsg = idMsg;
    pshop->msg = msg;
    switch (msg) {
    case -1:
        pshop->tMsg = -10.0f;
        break;
    case 0:
        pshop->tMsg = D_002A7984;
        SetSource__4CSndPv(PsndNewPlain__Fi(0x29), 0);
        break;
    case 1:
    default:
        pshop->tMsg = g_clock.tReal + D_002C3254;
        SetSource__4CSndPv(PsndNewPlain__Fi(0x36), 0);
        break;
    }
}
