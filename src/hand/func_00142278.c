/* The actor throws plo at ploTarget: plo fades in, becomes the throw's selected object (+0x11C0) aimed at the target's
 * position (+0x1290), the arc updated, the actor in state 7 (vt slot 88) and the throw in state 7. */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct ACTOR { char pad[0xC]; VTENT *vt; char pad2[0x11B0 - 0x10]; char jtthrow[0x10]; void *ploSelected; char pad3[0x1290 - 0x11C4]; qword posTarget; };
void FadeAloIn__FP3ALOf(void *pactor, float f);
qword PosOfLo__FP2LO(void *pactor);
void UpdateJtThrowArc__FP7JTTHROWi(void *pactor, int n);
void SetJtThrowState__FP7JTTHROWi(void *pactor, int n);
void func_00142278(struct ACTOR *pactor, void *plo, void *ploTarget)
{
    VTENT *e;
    FadeAloIn__FP3ALOf(plo, 0.25f);
    pactor->ploSelected = plo;
    pactor->posTarget = PosOfLo__FP2LO(ploTarget);
    UpdateJtThrowArc__FP7JTTHROWi(pactor->jtthrow, 0);
    e = &pactor->vt[88];
    ((void (*)(void *, int))e->pfn)(VT_THIS(pactor, e), 7);
    SetJtThrowState__FP7JTTHROWi(pactor->jtthrow, 7);
}
