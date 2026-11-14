typedef struct DL { void *pvFirst; void *pvLast; int ibDle; } DL;
typedef struct DLI { DL *pdl; void **ppv; int ibDle; struct DLI *pdliNext; } DLI;
#include "clock.h"
extern DLI *s_pdliFirst;
typedef struct {
    char pad[0x40];
    unsigned int x40;
    char pad44[0x5C - 0x44];
    DL dl;
    char pad68[0x70 - 0x68];
    float t;
    int x74;
} OBJ;
void UpdateLo__FP2LO(OBJ *);
void RunRun__FP4PRUN(void *);
int FIsDlEmpty__FP2DL(DL *);
void StopScptImpl__FP2LO(OBJ *);
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
void UpdateScpt__FP2LO(OBJ *p)
{
    DLI dli;
    void *pv;
    unsigned int fl;
    UpdateLo__FP2LO(p);
    if (p->x74 == 0)
        return;
    fl = p->x40;
    if ((fl ^ 1) & 1)
        fl = *(unsigned int *)fl;
    if (fl & 0x100)
        p->t += g_clock.dtReal;
    else
        p->t += g_clock.dt;
    InitDli(&dli, &p->dl);
    while ((pv = PvNextDli(&dli)) != 0)
        RunRun__FP4PRUN(pv);
    if (FIsDlEmpty__FP2DL(&p->dl))
        StopScptImpl__FP2LO(p);
    s_pdliFirst = dli.pdliNext;
}
