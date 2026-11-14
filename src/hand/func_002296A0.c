/* class: WATER (UpdateWater calls it): a slot from the water's own slot heap at +0x40E8. */
#include "slotheap.h"

typedef struct WATER {
    /* 0x0000 */ char pad0[0x40e8];
    /* 0x40e8 */ SLOTHEAP slotheap;
} WATER;
void *func_0011CCC0(SLOTHEAP *pslotheap);

void *func_002296A0(WATER *pwater)
{
    return func_0011CCC0(&pwater->slotheap);
}
