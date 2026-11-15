/* func_0020FAA0 (0x20FAA0): the collision entries (at most 0x100, from stack scratch memory) of the active
 * attachments whose box overlaps the box of posA..posB that the filter (if any) keeps, after the attachments are
 * brought up to date. */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct ALLOCREQ { int cb; int nAlign; };
/* a collision entry of an attachment (SOE): the next one */
struct SOE { char pad[0x60]; struct SOE *psoeNext; };
/* an attachment: its bounding box, entries, the next one */
struct OXA { float posMin[4]; float posMax[3]; char pad[0x34 - 0x1C]; struct SOE *psoeFirst; char pad2[0x40 - 0x38]; struct OXA *poxaNext; };
struct SW { char pad[0x3D1C]; struct OXA *poxaFirst; };   /* the active attachments */
void *PvAllocStackImpl__Fi(struct ALLOCREQ *preq);
void FlushSwOxaDirty1__FP2SW(struct SW *psw);
void UpdateSwAaox__FP2SW(struct SW *psw);

void func_0020FAA0(struct SW *psw, qword posA, qword posB, int (*pfn)(void *, struct SOE *), void *pvFilter, int *pcpsoe, struct SOE ***papsoe)
{
    U posMin, posMax;
    struct ALLOCREQ req;
    struct SOE **apsoe;
    struct OXA *poxa;
    int cpsoe;
    __asm__("vmini.xyz %0, %1, %2" : "=j"(posMin.q) : "j"(posA), "j"(posB)); __asm__("vmax.xyz %0, %1, %2" : "=j"(posMax.q) : "j"(posA), "j"(posB));
    {
        struct ALLOCREQ *preq = &req;
        preq->cb = 0x400;
        preq->nAlign = 0x10;
    }
    cpsoe = 0;
    apsoe = PvAllocStackImpl__Fi(&req);
    FlushSwOxaDirty1__FP2SW(psw);
    UpdateSwAaox__FP2SW(psw);
    for (poxa = psw->poxaFirst; poxa; poxa = poxa->poxaNext) {
        struct SOE *psoe;
        if (poxa->posMin[0] > posMax.f[0] || poxa->posMax[0] < posMin.f[0] ||
            poxa->posMin[1] > posMax.f[1] || poxa->posMax[1] < posMin.f[1] ||
            poxa->posMin[2] > posMax.f[2] || poxa->posMax[2] < posMin.f[2])
            continue;
        for (psoe = poxa->psoeFirst; psoe; psoe = psoe->psoeNext) {
            if (pfn && !pfn(pvFilter, psoe))
                continue;
            if (cpsoe < 0x100)
                apsoe[cpsoe++] = psoe;
        }
    }
    *papsoe = apsoe;
    *pcpsoe = cpsoe;
}
