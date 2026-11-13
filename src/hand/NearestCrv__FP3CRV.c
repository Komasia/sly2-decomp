/* NearestCrv: the point of a curve nearest a position, searching from parameter g: the linear (0x1E6A30) or the cubic
 * (0x1E6DB8) search. Outputs: the point, its direction, its parameter and its distance along the curve.
 * Layout: SafeHouse port (crv.h CRV). */
#include "crv.h"
#include "vec.h"

void func_001E6A30(CRV *pcrv, struct VECTOR *ppos, float g, struct VECTOR *pposNearest, struct VECTOR *pdir,
                   float *pg, float *ps);   /* SafeHouse: the linear curve's search */
void func_001E6DB8(CRV *pcrv, struct VECTOR *ppos, float g, struct VECTOR *pposNearest, struct VECTOR *pdir,
                   float *pg, float *ps);   /* SafeHouse: the cubic curve's search */

// name: SafeHouse port (NearestCrv)
void NearestCrv__FP3CRV(CRV *pcrv, struct VECTOR *ppos, float g, struct VECTOR *pposNearest, struct VECTOR *pdir,
                        float *pg, float *ps)
{
    if (pcrv->crvk == 0) {
        func_001E6A30(pcrv, ppos, g, pposNearest, pdir, pg, ps);
        return;
    }
    func_001E6DB8(pcrv, ppos, g, pposNearest, pdir, pg, ps);
}
