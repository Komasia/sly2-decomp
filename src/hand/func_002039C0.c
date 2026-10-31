/* func_002039C0 (0x2039C0): STEP virtual slot 13 (Load*FromBrx): PO load, then cache STEP::qwUnk240 from
 * func_001A6F00(parent, step, zero vector) and finish with func_001F8300. */
#include "step.h"

void func_001C3DC8(STEP *pstep, void *pbis);   /* PO slot 13 */
qword func_001A6F00(void *plo, STEP *pstep, qword qw);
int func_001F8300(STEP *pstep);   /* returns a value the caller ignores (declared int: void changes the code) */
extern qword D_002A2DD0;   /* (0, 0, 0, 0) */

void func_002039C0(STEP *pstep, void *pbis)
{
    qword qw;

    func_001C3DC8(pstep, pbis);
    qw = func_001A6F00(pstep->po.so.lo.psoParent, pstep, D_002A2DD0);

    pstep->qwUnk240 = qw;
    func_001F8300(pstep);
}
