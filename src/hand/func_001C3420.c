/* func_001C3420 (0x1C3420): class 11 virtual slot 21: LO slot 21 (func_001A6150), then remove the object from the class's object list
 * D_003E13C0 (slot 22 puts it back). */
#include "so.h"

void func_001A6150(LO *plo);
void RemoveDlEntry__FP2DLPv(DL *pdl, void *pv);
extern DL D_003E13C0;

void func_001C3420(LO *plo)
{
    func_001A6150(plo);
    RemoveDlEntry__FP2DLPv(&D_003E13C0, plo);
}
