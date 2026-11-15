/* UpdateScpt (vt slot 15): updates a firing relay: the LO update, advances its time since firing (on the real clock
 * with GRFUPD_RealTime), runs each of its scripts (JSGs), and stops the relay once no script is left. */
#include "relay.h"
#include "clock.h"
#include "h3_update.h"
typedef struct DLI { DL *pdl; void **ppv; int ibDle; struct DLI *pdliNext; } DLI;   /* list iterator (safe against removal) */
extern DLI *s_pdliFirst;
void UpdateLo__FP2LO(RELAY *);
void RunRun__FP4PRUN(void *);
int FIsDlEmpty__FP2DL(DL *);
void StopScptImpl__FP2LO(RELAY *);
static inline void InitDli(DLI *pdli, DL *pdl)
{
    pdli->pdl = pdl;
    pdli->ppv = (void **)pdl;
    pdli->ibDle = pdl->ibDle;
    pdli->pdliNext = s_pdliFirst;
    s_pdliFirst = pdli;
}
static inline void *PvNextDli(DLI *pdli)
{
    void *pv = *pdli->ppv;
    pdli->ppv = (void **)((char *)pv + pdli->ibDle);
    return pv;
}
// name: SafeHouse port (UpdateScpt)
void UpdateScpt__FP2LO(RELAY *prelay)
{
    DLI dli;
    void *pjsg;
    unsigned int grf;
    UpdateLo__FP2LO(prelay);
    if (prelay->fFiring == 0)
        return;
    grf = prelay->lo.grfUnk40;
    if ((grf ^ GRFUPD_Flags) & GRFUPD_Flags)
        grf = *(unsigned int *)grf;
    if (grf & GRFUPD_RealTime)
        prelay->tFired += g_clock.dtReal;
    else
        prelay->tFired += g_clock.dt;
    InitDli(&dli, &prelay->dlJsg);
    while ((pjsg = PvNextDli(&dli)) != 0)
        RunRun__FP4PRUN(pjsg);
    if (FIsDlEmpty__FP2DL(&prelay->dlJsg))
        StopScptImpl__FP2LO(prelay);
    s_pdliFirst = dli.pdliNext;
}
