/* func_001BADB8 (0x1BADB8): class 98 virtual slot 22: SO slot 22 (func_001F3EA8), then append the object to the class's object list
 * D_003E1450 (slot 21 removes it again). */
#include "so.h"

void func_001F3EA8(SO *pso);
void AppendDlEntry__FP2DLPv(DL *pdl, void *pv);
extern DL D_003E1450;

void func_001BADB8(SO *pso)
{
    func_001F3EA8(pso);
    AppendDlEntry__FP2DLPv(&D_003E1450, pso);
}
