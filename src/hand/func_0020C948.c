/* StartK3 (0x20C948): a KIND3's directional player started on an object: the player record cleared (twice: the
 * constructor's clear and the assignment's), given its vtable (an ASEGA listener, D_002DA9D0), the tuning, the
 * object and the ApplyAseg flags; it plays the second direction's clip and listens to it. Layout: SafeHouse port
 * (guard.h K3PLAY). */
#include "h6_guard.h"
extern char D_002DA9D0[];   /* the K3PLAY vtable */
struct K3PLAY {
    /* 0x00 */ int unk_0x00; int unk_0x04; int pad8;
    /* 0x0c */ void *pvt;
    /* 0x10 */ char vel[0x10];
    /* 0x20 */ int palo;
    /* 0x24 */ int pasega;
    /* 0x28 */ KIND3 *ptuning;
    /* 0x2c */ KIND3E *pcur;
    /* 0x30 */ int grf;
    /* 0x34 */ char pad34[0xC];
};
void *s1_memset(void *pv, int c, int cb) asm("memset");
void ApplyAsegCur(int paseg, int palo, int grf, int *ppasega, float t, float uWeight) asm("ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA");
void AddLoListener__FP2LOi(int pasega, struct K3PLAY *pk3play);
// name: SafeHouse port (StartK3)
void StartK3__FP5KIND3iiP6K3PLAY(KIND3 *ptuning, int palo, int grf, struct K3PLAY *pk3play)
{
    s1_memset(pk3play, 0, sizeof(*pk3play));
    s1_memset(pk3play, 0, sizeof(*pk3play));
    pk3play->ptuning = ptuning;
    pk3play->palo = palo;
    pk3play->pvt = D_002DA9D0;
    pk3play->grf = grf;
    pk3play->unk_0x00 = 0;
    pk3play->unk_0x04 = 0;
    ApplyAsegCur((int)ptuning->ae[1].u.paseg, palo, grf, &pk3play->pasega, 0.0f, 1.0f);
    AddLoListener__FP2LOi(pk3play->pasega, pk3play);
    pk3play->pcur = &ptuning->ae[1];
}
