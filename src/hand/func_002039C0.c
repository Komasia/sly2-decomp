/* LoadPoFromBrx__FP2POP18CBinaryInputStream (0x2039C0): STEP virtual slot 13 (Load*FromBrx): PO load, then cache STEP::qwUnk240 from
 * ConvertPos__FP2LOT0G9VU_VECTOR(parent, step, zero vector) and finish with PregentEnsure__FP3ALO. */
#include "step.h"

void func_001C3DC8(STEP *pstep, void *pbis);   /* PO slot 13 */
qword ConvertPos__FP2LOT0G9VU_VECTOR(void *plo, STEP *pstep, qword qw);
int PregentEnsure__FP3ALO(STEP *pstep);   /* returns a value the caller ignores (declared int: void changes the code) */
extern qword D_002A2DD0;   /* (0, 0, 0, 0) */

// name: SafeHouse port (LoadPoFromBrx)
void LoadPoFromBrx__FP2POP18CBinaryInputStream(STEP *pstep, void *pbis)
{
    qword qw;

    func_001C3DC8(pstep, pbis);
    qw = ConvertPos__FP2LOT0G9VU_VECTOR(pstep->po.so.lo.psoParent, pstep, D_002A2DD0);

    pstep->qwUnk240 = qw;
    PregentEnsure__FP3ALO(pstep);
}
