/* UpdateSwPox: the overlap of a pair of attachments (k 1: overlapping, 2: not, 0: as recorded, else the boxes and
 * the objects' overlap kinds decide): a new pair of overlap records when they start overlapping; when they stop, both
 * objects are told (vt slot 54), the records unlinked, the contacts freed with the objects woken unless still, and the
 * records freed. Layout: SafeHouse port (so.h OX / OXA, bbmark.cpp). */
#include "so.h"
struct OX { void *pxp; struct OX *poxNext; struct OX *poxOther; struct LO *psoOther; int fOverlap; };   /* field: SafeHouse port */
struct OXA { char pad[0x60]; struct LO *pso; struct OX *pox; };   /* field: SafeHouse port */
struct SW { char pad[0x3CF8]; char slotheapOx[4]; };
int FOverlapOxa__FP3OXAT0Pv(struct SW *, struct OXA *, struct OXA *);
struct OX *PoxAddSw__FP2SWP3OXAT1(struct SW *, struct OXA *, struct OXA *);
struct OX *PoxRemoveSw__FP2SWP3OXAT1(struct SW *, struct OXA *, struct OXA *);
void FreeSwXpList(struct SW *, void *) asm("FreeSwXpList__FP2SWP2XP");
void WakeAlo__FP3ALO(struct LO *);
void func_0011CD98(void *, struct OX *);
#define VCALL(po, n, T) ((T)(po)->pvt[n].pfn)(VT_THIS((po), &(po)->pvt[n])
// name: SafeHouse port (UpdateSwPox)
void UpdateSwPox__FP2SWP3OXAT1Uc(struct SW *psw, struct OXA *poxa, struct OXA *poxaOther, int k)
{
    struct OX *pox;
    struct OX *poxFound;
    int fOverlap;
    for (poxFound = poxa->pox; poxFound; poxFound = poxFound->poxNext) {
        if (poxFound->psoOther == poxaOther->pso)
            break;
    }
    switch (k) {
    case 1:
        fOverlap = 1;
        break;
    case 2:
        fOverlap = 0;
        break;
    case 0:
        fOverlap = 0;
        if (poxFound)
            fOverlap = poxFound->fOverlap;
        break;
    }
    pox = poxFound;
    if (fOverlap || FOverlapOxa__FP3OXAT0Pv(psw, poxa, poxaOther)) {
        if (!pox) {
            struct OX *pox2;
            poxFound = PoxAddSw__FP2SWP3OXAT1(psw, poxa, poxaOther);
            pox2 = PoxAddSw__FP2SWP3OXAT1(psw, poxaOther, poxa);
            poxFound->poxOther = pox2;
            pox2->poxOther = poxFound;
            pox = poxFound;
        }
    } else if (pox) {
        struct OX *pox1, *pox2;
        VCALL(poxa->pso, 54, void (*)(void *, struct LO *)), poxaOther->pso);
        VCALL(poxaOther->pso, 54, void (*)(void *, struct LO *)), poxa->pso);
        pox1 = PoxRemoveSw__FP2SWP3OXAT1(psw, poxa, poxaOther);
        pox2 = PoxRemoveSw__FP2SWP3OXAT1(psw, poxaOther, poxa);
        if (pox1->pxp) {
            FreeSwXpList(psw, pox1->pxp);
            if (!VCALL(pox1->psoOther, 62, int (*)(void *))))
                WakeAlo__FP3ALO(pox1->psoOther);
            if (!VCALL(pox2->psoOther, 62, int (*)(void *))))
                WakeAlo__FP3ALO(pox2->psoOther);
        }
        func_0011CD98(psw->slotheapOx, pox1);
        func_0011CD98(psw->slotheapOx, pox2);
        pox = 0;
    }
    if (pox) {
        pox->poxOther->fOverlap = fOverlap;
        pox->fOverlap = fOverlap;
    }
}
