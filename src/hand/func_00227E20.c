/* func_00227E20 (0x227E20): class 23 virtual slot 22: LO slot 22 (func_001A6178), then append the object to the class's object list
 * D_003E1480 (slot 21 removes it again). */
#include "so.h"

void func_001A6178(LO *plo);
void AppendDlEntry__FP2DLPv(DL *pdl, void *pv);
extern DL D_003E1480;

void func_00227E20(LO *plo)
{
    func_001A6178(plo);
    AppendDlEntry__FP2DLPv(&D_003E1480, plo);
}
