/* class: booty (SetBootyState calls it): a record taken from the slot heap D_003E1144 with the given value
 * and pushed on the object's +0xE8 list. */
#include "slotheap.h"

typedef struct BOOTYREC {
    /* 0x0 */ int n;
    /* 0x4 */ int pad4;
    /* 0x8 */ struct BOOTYREC *pnext;
} BOOTYREC;
typedef struct LOE8 {
    /* 0x00 */ char pad0[0xe8];
    /* 0xe8 */ BOOTYREC *prec;
} LOE8;

extern SLOTHEAP D_003E1144;
void *func_0011CCC0(SLOTHEAP *pslotheap);

void func_001CF578(LOE8 *plo, int n)
{
    BOOTYREC *prec = (BOOTYREC *)func_0011CCC0(&D_003E1144);

    prec->n = n;
    prec->pnext = plo->prec;
    plo->prec = prec;
}
