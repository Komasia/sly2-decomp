/* LoadAloFromBrx (0x231170): ALO virtual slot 13: read the ALO's own data (func_00231768), then the LO data
 * (func_0013F810). */
#include "so.h"

void func_00231768(ALO *palo, void *pbis);
void func_0013F810(ALO *palo, void *pbis);

void LoadAloFromBrx__FP3ALOP18CBinaryInputStream(ALO *palo, void *pbis)
{
    func_00231768(palo, pbis);
    func_0013F810(palo, pbis);
}
