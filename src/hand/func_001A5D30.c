/* func_001A5D30 (0x1A5D30): add a run record to the LO (func_001A5D58) whose callback is func_001A5D08. */
#include "so.h"

void **func_001A5D58(LO *plo);
void func_001A5D08(void);

void func_001A5D30(LO *plo)
{
    *func_001A5D58(plo) = (void *)func_001A5D08;
}
