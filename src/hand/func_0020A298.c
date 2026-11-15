#include "cid.h"
extern struct { float t; float dt; } g_clock;
extern float D_002C3DAC;   /* how long a just-seen source still surprises */
/* a detector entry: its state and when it was seen */
struct DETENTRY { int pad; int st; int pad2; float tC; };
struct GUARD { char pad[0x2C0]; long grfState; char pad2[0x3D0 - 0x2C8]; int n3D0; char pad3[0xF64 - 0x3D4]; void *pdet; };
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
long func_00207A20(int st);
struct DETENTRY *PdetentryFind__FP8DETECTORi(void *pdet, void *plo);
/* FGuardSurprised (0x20A298): whether a hit from psource takes the guard by surprise: not after +0x3D0; yes for Murray
 * (cid 0x36) unless the guard is cid 0x3A or in state 6; yes when the detector has not seen the source, or saw it
 * only just now; otherwise only in the states of grfMask. */
// name: SafeHouse port (FGuardSurprised)
int FGuardSurprised__FP5GUARDP2LOUl(struct GUARD *pguard, void *psource, long grfMask)
{
    struct DETENTRY *pdetentry;
    if (pguard->n3D0)
        goto ret0;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(psource, CID_MURRAY) && !FIsBasicDerivedFrom__FP5BASIC3CID(pguard, CID_GUNGUARD) && !(pguard->grfState & func_00207A20(6)))
        goto ret1;
    pdetentry = PdetentryFind__FP8DETECTORi(pguard->pdet, psource);
    if (!pdetentry)
        goto ret1;
    if (!pdetentry->st || g_clock.t - pdetentry->tC < D_002C3DAC)
        goto ret1;
    if (!(pguard->grfState & grfMask))
        goto ret0;
ret1:
    return 1;
ret0:
    return 0;
}
