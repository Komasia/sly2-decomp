/* func_001C33E8 (0x1C33E8): class 11 virtual slot 22: LO slot 22 (func_001A6178), then append the object to the class's object list
 * D_003E13C0 (slot 21 removes it again). */
#include "so.h"

void func_001A6178(LO *plo);
void AppendDlEntry__FP2DLPv(DL *pdl, void *pv);
extern DL D_003E13C0;

void func_001C33E8(LO *plo)
{
    func_001A6178(plo);
    AppendDlEntry__FP2DLPv(&D_003E13C0, plo);
}
