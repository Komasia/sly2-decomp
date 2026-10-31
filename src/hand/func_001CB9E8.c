/* func_001CB9E8 (0x1CB9E8): class 13 virtual slot 21: LO slot 21 (func_001A6150), then remove the object from the class's object list
 * D_003E13CC (slot 22 puts it back). */
#include "so.h"

void func_001A6150(LO *plo);
void RemoveDlEntry__FP2DLPv(DL *pdl, void *pv);
extern DL D_003E13CC;

void func_001CB9E8(LO *plo)
{
    func_001A6150(plo);
    RemoveDlEntry__FP2DLPv(&D_003E13CC, plo);
}
