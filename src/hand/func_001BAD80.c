/* func_001BAD80 (0x1BAD80): class 98 virtual slot 21: SO slot 21 (func_001F3E00), then remove the object from the class's object list
 * D_003E1450 (slot 22 puts it back). */
#include "so.h"

void func_001F3E00(SO *pso);
void RemoveDlEntry__FP2DLPv(DL *pdl, void *pv);
extern DL D_003E1450;

void func_001BAD80(SO *pso)
{
    func_001F3E00(pso);
    RemoveDlEntry__FP2DLPv(&D_003E1450, pso);
}
