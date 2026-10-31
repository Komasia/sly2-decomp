/* func_001839D0 (0x1839D0): class 88 virtual slot 21: SO slot 21 (func_001F3E00), then remove the object from the class's object list
 * D_003E13E4 (slot 22 puts it back). */
#include "so.h"

void func_001F3E00(SO *pso);
void RemoveDlEntry__FP2DLPv(DL *pdl, void *pv);
extern DL D_003E13E4;

void func_001839D0(SO *pso)
{
    func_001F3E00(pso);
    RemoveDlEntry__FP2DLPv(&D_003E13E4, pso);
}
