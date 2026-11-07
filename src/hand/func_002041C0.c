/* func_002041C0 (0x2041C0): STEP virtual slot 28 (translate to position): SO version, then recompute
 * STEP::qwUnk230 from STEP::qwUnk240 (ConvertPos__FP2LOT0G9VU_VECTOR). */
#include "step.h"

void SetAloPos__FP3ALOG9VU_VECTOR(SO *pso, qword pos);   /* SO slot 28 */
qword ConvertPos__FP2LOT0G9VU_VECTOR(void *plo, void *pv, qword qw);

void func_002041C0(STEP *pstep, qword pos)
{
    SetAloPos__FP3ALOG9VU_VECTOR(&pstep->po.so, pos);
    pstep->qwUnk230 = ConvertPos__FP2LOT0G9VU_VECTOR(pstep, 0, pstep->qwUnk240);
}
