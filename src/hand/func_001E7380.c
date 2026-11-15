/* NearestCrvS: NearestCrv searching from distance s (its parameter). */
#include "crv.h"

struct CNSTR;
float GFromCrvS__FP3CRVf(CRV *pcrv, float s);
void NearestCrv__FP3CRV(CRV *pcrv, qword pos, struct CNSTR *pcnstr, qword *pposNearest, qword *pdir, float *pg, float *ps, float g);
// name: SafeHouse port (NearestCrvS)
void NearestCrvS__FP3CRVG9VU_VECTORPvP6VECTORT3PfT5f(CRV *pcrv, qword pos, struct CNSTR *pcnstr, qword *pposNearest, qword *pdir, float *pg, float *ps, float s)
{
    NearestCrv__FP3CRV(pcrv, pos, pcnstr, pposNearest, pdir, pg, ps, GFromCrvS__FP3CRVf(pcrv, s));
}
