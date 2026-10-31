/* func_0022D778 (0x22D778): SO virtual slot 50: func_0022D6B0(n, parent, pso). */
#include "so.h"

void func_0022D6B0(int n, SO *psoParent, SO *pso);

void func_0022D778(SO *pso, int n)
{
    func_0022D6B0(n, pso->lo.psoParent, pso);
}
