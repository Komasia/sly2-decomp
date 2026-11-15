/* func_001E69A0: the function NearestCrv's cubic search (0x1E6DB8) minimizes: the squared distance from the
 * context's position to the curve's point at parameter g; with a constraint, of the difference projected by it
 * (ProjectCnstrLocal, e.g. the horizontal plane). */
#include "crv.h"

struct CNSTR;
/* the search's context (0x1E6DB8) */
struct NEARCTX { CRV *pcrv; struct CNSTR *pcnstr; int pad[2]; qword pos; };
void EvalCrv__FP3CRVfP6VECTORT2(CRV *pcrv, float g, qword *ppos, qword *pdir);
qword ProjectCnstrLocal__FP6CNSTRSG9VU_VECTOR(struct CNSTR *pcnstr, qword v);
static inline qword SquareBits(qword a) {
    register qword d __asm__("vf1"),one __asm__("vf3");
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(a));
    return d;
}
static inline qword ConvertedSquareBits(qword a) {
    register qword value __asm__("vf4");
    register qword square __asm__("vf1"),one __asm__("vf2");
    __asm__("qmtc2.ni %1,%0":"=j"(value):"r"(a));
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(square),"=&j"(one):"j"(value));
    return square;
}
float func_001E69A0(void *pv, float g)
{
    struct NEARCTX *pctx = (struct NEARCTX *)pv;
    qword posCrv;
    register qword bits __asm__("$2");
    float result;
    EvalCrv__FP3CRVfP6VECTORT2(pctx->pcrv, g, &posCrv, 0);
    if (!pctx->pcnstr) {
        register qword point __asm__("vf1") = pctx->pos;
        register qword path __asm__("vf2") = posCrv;
        __asm__("vsub.xyzw %0,%0,%1" : "+j"(point) : "j"(path));
        bits = SquareBits(point);
    } else {
        register qword point __asm__("vf2") = pctx->pos;
        register qword path __asm__("vf1") = posCrv;
        register qword delta __asm__("vf3");
        __asm__("vsub.xyzw %0,%1,%2" : "=j"(delta) : "j"(path), "j"(point));
        bits = ConvertedSquareBits(ProjectCnstrLocal__FP6CNSTRSG9VU_VECTOR(pctx->pcnstr, delta));
    }
    __asm__ __volatile__("mtc1 %1,%0" : "=f"(result) : "r"(bits));
    return result;
}
