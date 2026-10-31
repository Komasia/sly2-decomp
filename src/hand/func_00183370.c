/* func_00183370 (0x183370): class 34 virtual slot 22: LO slot 22 (func_001A6178), then append the object to the class's object list
 * D_003E13FC (slot 21 removes it again). */
#include "so.h"

void func_001A6178(LO *plo);
void AppendDlEntry__FP2DLPv(DL *pdl, void *pv);
extern DL D_003E13FC;

void func_00183370(LO *plo)
{
    func_001A6178(plo);
    AppendDlEntry__FP2DLPv(&D_003E13FC, plo);
}
