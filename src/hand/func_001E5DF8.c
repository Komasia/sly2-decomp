/* LoadPathFromBrx: load a path object: the located-object base, the curve kind and closed flag, the points'
 * parameters and positions, for a cubic curve the in / out tangents, then the options; the distances are then
 * computed for its world matrix (RecalcCrv). Layout: crv.h CRV. */
#include "crv.h"

struct CBinaryInputStream;
/* an allocation request: the size and the alignment */
struct ALLOC { int cb; int cbAlign; };
void LoadLoxBaseFromBrx(CRV *pcrv, struct CBinaryInputStream *pbis);
int S8Read(struct CBinaryInputStream *pbis) asm("S8Read__18CBinaryInputStream");
int U16Read(struct CBinaryInputStream *pbis) asm("U16Read__18CBinaryInputStream");
void *PvAllocSwImpl__Fi(struct ALLOC *palloc);
void Read__18CBinaryInputStreamiPv(struct CBinaryInputStream *pbis, int cb, void *pv);
void ReadVector__18CBinaryInputStreamP6VECTOR(struct CBinaryInputStream *pbis, qword *pvec);
void LoadOptionsFromBrx__FPvP18CBinaryInputStream(CRV *pcrv, struct CBinaryInputStream *pbis);
void RecalcCrv__FP3CRV(CRV *pcrv);

// name: SafeHouse port (LoadPathFromBrx)
void LoadPathFromBrx__FP2LOP18CBinaryInputStream(CRV *pcrv, struct CBinaryInputStream *pbis)
{
    struct ALLOC alloc;
    int i;
    LoadLoxBaseFromBrx(pcrv, pbis);
    pcrv->crvk = S8Read(pbis);
    pcrv->fClosed = S8Read(pbis);
    pcrv->cpoint = U16Read(pbis);
    alloc.cb = pcrv->cpoint * 4;
    alloc.cbAlign = 0x10;
    pcrv->ag = PvAllocSwImpl__Fi(&alloc);
    alloc.cb = pcrv->cpoint * 4;
    alloc.cbAlign = 0x10;
    pcrv->as = PvAllocSwImpl__Fi(&alloc);
    alloc.cb = pcrv->cpoint * 16;
    alloc.cbAlign = 0x10;
    pcrv->apos = PvAllocSwImpl__Fi(&alloc);
    Read__18CBinaryInputStreamiPv(pbis, pcrv->cpoint * 4, pcrv->ag);
    for (i = 0; i < pcrv->cpoint; i++)
        ReadVector__18CBinaryInputStreamP6VECTOR(pbis, &pcrv->apos[i]);
    if (pcrv->crvk != CRVK_Linear) {
        alloc.cb = pcrv->cpoint * 16;
        alloc.cbAlign = 0x10;
        pcrv->avIn = PvAllocSwImpl__Fi(&alloc);
        alloc.cb = pcrv->cpoint * 16;
        alloc.cbAlign = 0x10;
        pcrv->avOut = PvAllocSwImpl__Fi(&alloc);
        for (i = 0; i < pcrv->cpoint; i++)
            ReadVector__18CBinaryInputStreamP6VECTOR(pbis, &pcrv->avIn[i]);
        for (i = 0; i < pcrv->cpoint; i++)
            ReadVector__18CBinaryInputStreamP6VECTOR(pbis, &pcrv->avOut[i]);
    }
    LoadOptionsFromBrx__FPvP18CBinaryInputStream(pcrv, pbis);
    RecalcCrv__FP3CRV(pcrv);
}
