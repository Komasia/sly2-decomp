/* class: CSndVoice: its slot returned to the slot heap D_003DD074 (its Release 0x1FCCA0 calls it at the last reference). */
#include "slotheap.h"

extern SLOTHEAP D_003DD074;
void func_0011CD98(SLOTHEAP *pslotheap, void *pv);

void func_001FCD10(void *psnd)
{
    func_0011CD98(&D_003DD074, psnd);
}
