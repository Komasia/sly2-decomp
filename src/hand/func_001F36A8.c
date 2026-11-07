/* func_001F36A8 (0x1F36A8): SO virtual slot 14 (Post*Load): LO post-load, then the SO's own fix-ups and its
 * glob set. */
#include "so.h"

void PostLoLoad__FP2LO(LO *plo);
void UpdateAloXfWorlds__FP3ALO(SO *pso);
void func_00167B68(void *pglobset);

void func_001F36A8(SO *pso)
{
    PostLoLoad__FP2LO(&pso->lo);
    UpdateAloXfWorlds__FP3ALO(pso);
    func_00167B68(pso->globset);
}
