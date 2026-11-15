/* func_0020FC60 (0x20FC60): the collision entries (at most 0x100, from stack scratch memory) of the active
 * attachments whose sphere meets the sphere (pos, sRadius) that the filter (if any) keeps. */
typedef int qword __attribute__((mode(TI)));
struct ALLOCREQ { int cb; int nAlign; };
/* a collision entry of an attachment (SOE): the next one */
struct SOE { char pad[0x60]; struct SOE *psoeNext; };
/* an attachment: its bounding sphere, entries, the next one */
struct OXA { char pad[0x20]; qword posCenter; float sRadius; struct SOE *psoeFirst; char pad2[0x40 - 0x38]; struct OXA *poxaNext; };
struct SW { char pad[0x3D1C]; struct OXA *poxaFirst; };   /* the active attachments */
void *PvAllocStackImpl__Fi(struct ALLOCREQ *preq);
void FlushSwOxaDirty1__FP2SW(struct SW *psw);
void UpdateSwAaox__FP2SW(struct SW *psw);

void func_0020FC60(struct SW *psw, qword pos, float sRadius, int (*pfn)(void *, struct SOE *), void *pvFilter, int *pcpsoe, struct SOE ***papsoe)
{
    struct ALLOCREQ req;
    struct SOE **apsoe;
    struct OXA *poxa;
    int cpsoe;
    req.cb = 0x400;
    req.nAlign = 0x10;
    apsoe = PvAllocStackImpl__Fi(&req);
    cpsoe = 0;
    FlushSwOxaDirty1__FP2SW(psw);
    UpdateSwAaox__FP2SW(psw);
    for (poxa = psw->poxaFirst; poxa; poxa = poxa->poxaNext) {
        float sSum;
        qword d, e, tmp;
        float f;
        struct SOE *psoe;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(pos), "j"(poxa->posCenter));
        __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(e), "=&j"(tmp) : "0"(d));
        sSum = sRadius + poxa->sRadius;
        sSum *= sSum;
        __asm__("mtc1 %1, %0" : "=f"(f) : "r"(e));
        if (sSum < f)
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
