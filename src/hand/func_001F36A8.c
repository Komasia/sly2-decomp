/* func_001F36A8 (0x1F36A8): SO virtual slot 14 (Post*Load): LO post-load, then the SO's own fix-ups and its
 * glob set. */
#include "so.h"

void PostLoLoad__FP2LO(LO *plo);
void func_0022FAA0(SO *pso);
void func_00167B68(void *pglobset);

void func_001F36A8(SO *pso)
{
    PostLoLoad__FP2LO(&pso->lo);
    func_0022FAA0(pso);
    func_00167B68(pso->globset);
}
