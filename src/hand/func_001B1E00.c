/* LoadMissileFromBrx (0x1B1E00): MISSILE virtual slot 13: SO load, then func_001A64E8(pmissile, 1, D_002C0258). */
#include "bomb.h"

void LoadSoFromBrx__FP2SOP18CBinaryInputStream(SO *pso, void *pbis);
void func_001A64E8(MISSILE *pmissile, int n, void *pv);
extern char D_002C0258[];

void LoadMissileFromBrx__FP7MISSILEP18CBinaryInputStream(MISSILE *pmissile, void *pbis)
{
    LoadSoFromBrx__FP2SOP18CBinaryInputStream(&pmissile->bomb.so, pbis);
    func_001A64E8(pmissile, 1, D_002C0258);
}
