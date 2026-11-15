/* MATCH (Claude agent laneB14, 2026-10-23), from v2 (3). One register pin (k3 in s5) plus commented empty asms:
 * - an empty asm after `paox = aaox` keeps the loop-made i+1 (addiu s4) last in its block, so reorg puts it in the b slot;
 * - that asm lengthens aaox's live range by one insn, which drops aaox's global-alloc priority below psw's (s2/s3 swap).
 *   Five empty asms after the first loop add the same length to psw's range (they stand in for ~5 insns the original
 *   had there), restoring the target's psw/aaox priority order;
 * - paaox is set (before k3) so the aae address is computed ahead of the k3 constant, as in the target. */
/* RemoveSwOxa (RemoveSwAaobrObject): an attachment leaves the world: each overlap record pair is undone (both
 * objects told by vt slot 54, the other side's record unlinked, a still contact partner woken, the contacts freed) and
 * freed, its sensor contacts freed, it leaves the attachment lists, its two entries leave each sweep list, and it is
 * freed. Layout: SafeHouse port (so.h OX / OXA / AOX / PHYSW, bbmark.cpp). */
/* v2 (Claude agent laneB12, 2026-10-23): aligned 7 -> 3. The /12 pointer-diff divisions written out as (bytes * k3) >> 2 with k3 = 0xAAAAAAAB in ONE commented register pin ($21 = s5, as in the target): fixes the s4/s5 swap. Left: ori s5 before addiu fp, and i+1 (addiu s4) scheduled right after the sll instead of in the b delay slot (j = i + 1 / i = j step, split init: same 3). */
#include "so.h"
struct OXA;
struct OX { void *pxp; struct OX *poxNext; struct OX *poxOther; struct LO *psoOther; int fOverlap; };   /* field: SafeHouse port */
struct SOX { char pad[0xEC]; struct OXA *poxa; };   /* the SO's attachment (+0xEC) */
struct OXA { char pad[0x60]; struct LO *pso; struct OX *pox; int pxpInternal; void *pxpSensor; unsigned long grf; };   /* field: SafeHouse port */
struct AOX { int fMax; struct OXA *poxa; int pg; };   /* field: SafeHouse port */
struct SW { char pad[0x3CD0]; int caox; struct AOX *aaox[3]; char slotheapOxa[0x3CF8 - 0x3CE0]; char slotheapOx[0x3D10 - 0x3CF8];
    char dlOxa[0xC]; char dlOxaActive[0xC]; char dlOxaDirty1[0xC]; char dlOxaDirty2[0xC]; };   /* field: SafeHouse port (PHYSW) */
struct OX *PoxRemoveSw__FP2SWP3OXAT1(struct SW *, struct OXA *, struct OXA *);
void FreeSwXpList(struct SW *, void *) asm("FreeSwXpList__FP2SWP2XP");
void WakeAlo__FP3ALO(struct LO *);
void func_0011CD98(void *, void *);
void RemoveDlEntry__FP2DLPv(void *, struct OXA *);
int FFindDlEntry__FP2DLPv(void *, struct OXA *);
void *s1_memmove(void *, void *, int) asm("memmove");
#define VCALL(po, n, T) ((T)(po)->pvt[n].pfn)(VT_THIS((po), &(po)->pvt[n])
// name: SafeHouse port (RemoveSwOxa)
void RemoveSwOxa__FP2SWP3OXA(struct SW *psw, struct OXA *poxa)
{
    struct OX *pox, *poxNext;
    int i;
    for (pox = poxa->pox; pox; pox = poxNext) {
        struct OX *poxOther;
        VCALL(poxa->pso, 54, void (*)(void *, struct LO *)), pox->psoOther);
        VCALL(pox->psoOther, 54, void (*)(void *, struct LO *)), poxa->pso);
        poxOther = PoxRemoveSw__FP2SWP3OXAT1(psw, ((struct SOX *)pox->psoOther)->poxa, poxa);
        if (pox->pxp) {
            if (!VCALL(pox->psoOther, 62, int (*)(void *))))
                WakeAlo__FP3ALO(pox->psoOther);
            FreeSwXpList(psw, pox->pxp);
        }
        poxNext = pox->poxNext;
        func_0011CD98(psw->slotheapOx, pox);
        func_0011CD98(psw->slotheapOx, poxOther);
    }
    /* five empty asms: lengthen psw's live range (global-alloc priority), emulating the original insn count here */
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    FreeSwXpList(psw, poxa->pxpSensor);
    RemoveDlEntry__FP2DLPv(psw->dlOxa, poxa);
    if (FFindDlEntry__FP2DLPv(psw->dlOxaActive, poxa))
        RemoveDlEntry__FP2DLPv(psw->dlOxaActive, poxa);
    if ((poxa->grf & 1) == 1)
        RemoveDlEntry__FP2DLPv(psw->dlOxaDirty1, poxa);
    if (poxa->grf & 2)
        RemoveDlEntry__FP2DLPv(psw->dlOxaDirty2, poxa);
    {
    struct AOX **paaox;
    register unsigned int k3 __asm__("$21");
    i = 0;
    paaox = psw->aaox;
    k3 = 0xAAAAAAAB;  /* register pin: the exact-/12 multiplier (target s5) */
    for (; i < 3; i++) {
        struct AOX *aaox = ((struct SW *)((char *)paaox - 0x3CD4))->aaox[i];  /* = psw->aaox[i]; this form keeps the addu base-first */
        struct AOX *paox = aaox;
        struct AOX *paoxMin;
        __asm__ __volatile__("");  /* keeps i+1 after paox = aaox, so reorg puts it in the b delay slot */
        while (1) {
            while (paox->poxa != poxa)
                paox++;
            if (paox->fMax)
                break;
            paoxMin = paox++;
        }
        s1_memmove(paoxMin, paoxMin + 1, ((int)(((char *)paox - (char *)paoxMin) * k3) >> 2) * sizeof(struct AOX) - sizeof(struct AOX));
        s1_memmove(paox - 1, paox + 1, (psw->caox - ((int)(((char *)paox - (char *)aaox) * k3) >> 2)) * sizeof(struct AOX) - sizeof(struct AOX));
    }
    }
    psw->caox -= 2;
    func_0011CD98(psw->slotheapOxa, poxa);
}
