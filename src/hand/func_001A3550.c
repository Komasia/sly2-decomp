/* func_001A3550 (0x1A3550): LIGHT virtual slot 28 (translate to position): ALO version, then rebuild the light. */
#include "light.h"

void func_002312A0(ALO *palo, qword pos);

void func_001A3550(LIGHT *plight, qword pos)
{
    func_002312A0(&plight->alo, pos);
    func_001A3968(plight);
}
