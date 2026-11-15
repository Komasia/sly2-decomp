/* func_00204ED8 (0x204ED8): the velocity of the actor's animation root channel (kind 6) of pasega at its local time over dt
 * (the channel's vt slot 3); zero when there is no ASEGA, it is retracted, or it has no such channel. */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
extern qword D_002A2DD0;
/* an animation channel */
struct ACHN { VTENT *pvt; };
/* PchnFindAseg's result */
struct ASEGCHN { int unk_0x00; struct ACHN *pchn; };
struct ASEG;
struct ASEGA { char pad[0x14]; struct ASEG *paseg; char pad2[0x40 - 0x18]; float tLocal; };
int FAsegaRetracted(struct ASEGA *pasega) asm("FAsegaRetracted__FP5ASEGA");
struct ASEGCHN *PchnFindAseg__FP4ASEGP3ALOPvi(struct ASEG *paseg, void *palo, int chnk, int fRequire);
qword func_00204ED8(void *pactor, struct ASEGA *pasega, float dt)
{
    qword vel = D_002A2DD0;
    if (pasega && !FAsegaRetracted(pasega)) {
        struct ASEGCHN *pchnentry = PchnFindAseg__FP4ASEGP3ALOPvi(pasega->paseg, pactor, 6, 1);
        if (pchnentry) {
            struct ACHN *pchn = pchnentry->pchn;
            ((void (*)(void *, qword *, qword *, float, float))pchn->pvt[3].pfn)(VT_THIS(pchn, &pchn->pvt[3]), 0, &vel, dt, pasega->tLocal);
        }
    }
    return vel;
}
