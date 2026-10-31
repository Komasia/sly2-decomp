/* func_001FF470 (0x1FF470): class 39 virtual slot 21: LO slot 21 (func_001A6150), then remove the object from the class's object list
 * D_003E13D8 (slot 22 puts it back). */
#include "so.h"

void func_001A6150(LO *plo);
void RemoveDlEntry__FP2DLPv(DL *pdl, void *pv);
extern DL D_003E13D8;

void func_001FF470(LO *plo)
{
    func_001A6150(plo);
    RemoveDlEntry__FP2DLPv(&D_003E13D8, plo);
}
