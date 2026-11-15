/* PlayActorScriptAnim: the actor plays the object oid (nearest to it; -1 ends the script animation): an ASEG applied
 * over the current animation, or a state machine replacing the current one, with the flags grfapl, the actor in the
 * state (vt slot 88). Layout: SafeHouse port (actor.h +0x1030 pasega / +0x1034 psma). */
#include "cid.h"
#include "vtbl.h"
struct ACTOR { char pad[0xC]; VTENT *vt; char pad2[0x1030 - 0x10]; char pasega[4]; char psma[4]; };
extern char g_sw[];
void EndActorScriptAnim__FP5ACTOR(struct ACTOR *pactor);
void *PloFindSwNearest__FP2LO3OIDii(void *g, int k, int oid, struct ACTOR *pactor);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *plo, int n);
void ClearSmaHandle__FPP3SMA(void *pactor);
void ApplyAsegCur(void *plo, struct ACTOR *pactor, int a, void *b, float f, float g) asm("ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA");
void RetractAsegaPp__FPP5ASEGA(void *pactor);
void ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(void *plo, struct ACTOR *pactor, int n, int a, void *b);
// name: SafeHouse port (PlayActorScriptAnim)
void PlayActorScriptAnim__FP2LOiii(struct ACTOR *pactor, int oid, int grfapl, int state)
{
    void *plo;
    if (oid == -1) {
        EndActorScriptAnim__FP5ACTOR(pactor);
        return;
    }
    plo = PloFindSwNearest__FP2LO3OIDii(g_sw, 1, oid, pactor);
    if (!plo) return;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(plo, CID_ASEG)) {
        ((void (*)(void *, int))pactor->vt[88].pfn)(VT_THIS(pactor, &pactor->vt[88]), state);
        ClearSmaHandle__FPP3SMA(pactor->psma);
        ApplyAsegCur(plo, pactor, grfapl, pactor->pasega, 0.0f, 1.0f);
    } else if (FIsBasicDerivedFrom__FP5BASIC3CID(plo, CID_SM)) {
        ((void (*)(void *, int))pactor->vt[88].pfn)(VT_THIS(pactor, &pactor->vt[88]), state);
        RetractAsegaPp__FPP5ASEGA(pactor->pasega);
        ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(plo, pactor, -1, grfapl, pactor->psma);
    }
}
