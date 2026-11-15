/* StopScptImpl: stops a firing relay: clears the firer and the time, retires each running script (JSG), forgets its
 * alarms, takes it off the update list if firing put it there, and sends the Splice event 6 (stopped, vt slot 3). */
#include "relay.h"
#include "h3_update.h"
#define SPLICEEVENT_Stopped 6
typedef void (*PFNSPLICEEVENT)(void *plo, int event, int, int, int, int);
typedef struct DLI { DL *pdl; void **ppv; int ibDle; struct DLI *pdliNext; } DLI;   /* list iterator (safe against removal) */
extern DLI *s_pdliFirst;
void RetireRun__FP4PRUN(void *pjsg);
void func_001E0120(RELAY *prelay);            /* forget the alarms */
void func_001A6CA8(RELAY *, int);             /* update list: 1 add, 2 remove (SafeHouse SetLoSt) */
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
// name: SafeHouse port (StopScptImpl)
void StopScptImpl__FP2LO(RELAY *prelay)
{
    DLI dli;
    void *pjsg;
    if (prelay->fFiring == 0)
        return;
    prelay->ploFirer = 0;
    prelay->tFired = 0.0f;
    prelay->fFiring = 0;
    InitDli(&dli, &prelay->dlJsg);
    while ((pjsg = PvNextDli(&dli)) != 0)
        RetireRun__FP4PRUN(pjsg);
    func_001E0120(prelay);
    if (prelay->fUpdating) {
        func_001A6CA8(prelay, 2);
        if ((prelay->lo.grfUnk40 ^ GRFUPD_Flags) & GRFUPD_Flags)
            *(int *)prelay->lo.grfUnk40 &= ~GRFUPD_Update;
        else
            prelay->lo.grfUnk40 &= ~GRFUPD_Update;
    }
    ((PFNSPLICEEVENT)prelay->lo.pvt[3].pfn)(VT_THIS(prelay, &prelay->lo.pvt[3]), SPLICEEVENT_Stopped, 0, 0, 0, 0);
    s_pdliFirst = dli.pdliNext;
}
