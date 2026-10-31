/* func_0013AA70 (0x13AA70): BOMB virtual slot 75: SO clone, then make the bomb its own owner (func_0013BC60). */
#include "bomb.h"

void CloneSo__FP2SOT0(SO *pso, SO *psoBase);
void func_0013BC60(BOMB *pbomb, SO *psoOwner);

void func_0013AA70(BOMB *pbomb, BOMB *pbombBase)
{
    CloneSo__FP2SOT0(&pbomb->so, &pbombBase->so);
    func_0013BC60(pbomb, &pbomb->so);
}
