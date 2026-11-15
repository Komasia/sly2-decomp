#include "vtbl.h"
struct NOISE { char pad[0xC]; VTENT *vt; };
struct JOBINVESTIGATE { char pad[0x44]; struct NOISE *pnoise; int fNew; };
/* JOBINVESTIGATE::SetNoise: follow another noise: the old one released (vtable entry 2), the new one referenced
 * (entry 1), and the job told there is a new noise. */
// name: SafeHouse port (JOBINVESTIGATE::SetNoise)
void SetNoise__14JOBINVESTIGATEP5NOISE(struct JOBINVESTIGATE *pjob, struct NOISE *pnoiseNew) {
    if (pnoiseNew == pjob->pnoise) return;
    if (pjob->pnoise) { VTENT *pvte = &pjob->pnoise->vt[2]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjob->pnoise, pvte)); }
    pjob->pnoise = pnoiseNew;
    if (pnoiseNew) { VTENT *pvte = &pnoiseNew->vt[1]; ((void (*)(void *))pvte->pfn)(VT_THIS(pnoiseNew, pvte)); }
    pjob->fNew = 1;
}
