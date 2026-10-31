/* func_001A6DC0 (0x1A6DC0): LO virtual slot 45: set the LO's visibility flags (LO::grfvis). */
#include "so.h"

void func_001A6DC0(LO *plo, char grfvis)
{
    plo->grfvis = grfvis;
}
