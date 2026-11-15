/* SetRopeEnd: end iend of a rope on object plo: the object's point in its record (vt slot 32 gives the record and
 * the point), else the path's own end (its first / last parameter's point) in the world. Layout: h3_rope.h ROPE. */
#include "so.h"
#include "h3_rope.h"

/* vt slot 32's output: a frame whose last row is the point */
struct M4 { qword r[3]; qword pos; };
extern char D_002C44F0[];   /* the world's record */
float GMinCrv__FP3CRV(CRV *pcrv);
float GMaxCrv__FP3CRV(CRV *pcrv);
void EvalCrv__FP3CRVfP6VECTORT2(CRV *pcrv, qword *ppos, int pdir, float g);
// name: SafeHouse port (SetRopeEnd)
void SetRopeEnd__FP4ROPEiP2LO(ROPE *prope, int iend, struct LO *plo)
{
    prope->apo[iend] = plo;
    if (plo) {
        struct M4 m;
        VTENT *pe = &plo->pvt[32];
        prope->apxf[iend] = ((struct XF *(*)(void *, struct M4 *))pe->pfn)(VT_THIS(plo, pe), &m);
        *(prope->apos + iend) = m.pos;
    } else {
        float g;
        prope->apxf[iend] = (struct XF *)D_002C44F0;
        if (iend == 0)
            g = GMinCrv__FP3CRV(prope->ppath);
        else
            g = GMaxCrv__FP3CRV(prope->ppath);
        EvalCrv__FP3CRVfP6VECTORT2(prope->ppath, &prope->apos[iend], 0, g);
    }
}
