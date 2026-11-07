/* func_0013AA70 (0x13AA70): BOMB virtual slot 75: SO clone, then make the bomb its own owner (SetProjectileLauncher__FP3ALOP2LO). */
#include "bomb.h"

void CloneSo__FP2SOT0(SO *pso, SO *psoBase);
void SetProjectileLauncher__FP3ALOP2LO(BOMB *pbomb, SO *psoOwner);

void func_0013AA70(BOMB *pbomb, BOMB *pbombBase)
{
    CloneSo__FP2SOT0(&pbomb->so, &pbombBase->so);
    SetProjectileLauncher__FP3ALOP2LO(pbomb, &pbomb->so);
}
