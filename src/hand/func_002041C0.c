/* func_002041C0 (0x2041C0): STEP virtual slot 28 (translate to position): SO version, then recompute
 * STEP::qwUnk230 from STEP::qwUnk240 (func_001A6F00). */
#include "step.h"

void func_001F40A0(SO *pso, qword pos);   /* SO slot 28 */
qword func_001A6F00(void *plo, void *pv, qword qw);

void func_002041C0(STEP *pstep, qword pos)
{
    func_001F40A0(&pstep->po.so, pos);
    pstep->qwUnk230 = func_001A6F00(pstep, 0, pstep->qwUnk240);
}
