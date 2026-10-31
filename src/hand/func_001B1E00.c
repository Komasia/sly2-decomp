/* LoadMissileFromBrx (0x1B1E00): MISSILE virtual slot 13: SO load, then func_001A64E8(pmissile, 1, s_asnipMissile). */
#include "bomb.h"

void LoadSoFromBrx__FP2SOP18CBinaryInputStream(SO *pso, void *pbis);
void func_001A64E8(MISSILE *pmissile, int n, void *pv);
extern char s_asnipMissile[];

void LoadMissileFromBrx__FP7MISSILEP18CBinaryInputStream(MISSILE *pmissile, void *pbis)
{
    LoadSoFromBrx__FP2SOP18CBinaryInputStream(&pmissile->bomb.so, pbis);
    func_001A64E8(pmissile, 1, s_asnipMissile);
}
