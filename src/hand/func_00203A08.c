/* func_00203A08 (0x203A08): STEP virtual slot 40 (Clone*): PO clone, then fix up the behaviour stack. */
#include "step.h"

void ClonePo__FP2POT0(STEP *pstep, STEP *pstepBase);   /* PO slot 40 */
void func_001EEC68(void *pbhvstk, STEP *pstep);

void func_00203A08(STEP *pstep, STEP *pstepBase)
{
    ClonePo__FP2POT0(pstep, pstepBase);
    func_001EEC68(pstep->bhvstk, pstep);
}
