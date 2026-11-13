/* GetBentleyCpdefi (Bentley's vt slot 50): the camera target: a state other than 0 / 9 with an interaction under way
 * keeps +0x1080 at now; the actor's camera target (GetActorCmTarget), then state 13 (on a pipe) the climb's
 * (0x19EA00 on the climb at +0xF50) and state 5 the flag 1. Source: SafeHouse port (gang.cpp). */
#include "clock.h"

struct CPDEFI {
    /* 0x0 */ int grfcpd;          /* field: SafeHouse port */
};
struct BENTLEY {
    /* 0x0000 */ char pad0[0x4cc];
    /* 0x04cc */ int nSub4CC;      /* field: SafeHouse port */
    /* 0x04d0 */ char pad4D0[0xf50 - 0x4d0];
    /* 0x0f50 */ char climb[0x1080 - 0xf50];   /* the climb (actor.h CLIMB) */
    /* 0x1080 */ float t1080;      /* field: SafeHouse port */
    /* 0x1084 */ char pad1084[0x13d0 - 0x1084];
    /* 0x13d0 */ int state;        /* field: SafeHouse port */
};
void GetActorCmTarget__FP5ACTORP9ACTORPOSE(struct BENTLEY *pbentley, struct CPDEFI *pcpdefi);
void func_0019EA00(void *pclimb, struct CPDEFI *pcpdefi);   /* the climb's camera target */

// name: SafeHouse port (GetBentleyCpdefi)
void GetBentleyCpdefi__FP7BENTLEYP9ACTORPOSE(struct BENTLEY *pbentley, struct CPDEFI *pcpdefi)
{
    int state = pbentley->state;
    if (state != 0) {
        if (state != 9 && pbentley->nSub4CC != 0)
            pbentley->t1080 = g_clock.t;
    }
    GetActorCmTarget__FP5ACTORP9ACTORPOSE(pbentley, pcpdefi);
    switch (pbentley->state) {
    case 13:
        func_0019EA00(pbentley->climb, pcpdefi);
        return;
    case 5:
        pcpdefi->grfcpd |= 1;
        return;
    }
}
