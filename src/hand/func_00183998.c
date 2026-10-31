/* func_00183998 (0x183998): class 88 virtual slot 22: SO slot 22 (func_001F3EA8), then append the object to the class's object list
 * D_003E13E4 (slot 21 removes it again). */
#include "so.h"

void func_001F3EA8(SO *pso);
void AppendDlEntry__FP2DLPv(DL *pdl, void *pv);
extern DL D_003E13E4;

void func_00183998(SO *pso)
{
    func_001F3EA8(pso);
    AppendDlEntry__FP2DLPv(&D_003E13E4, pso);
}
