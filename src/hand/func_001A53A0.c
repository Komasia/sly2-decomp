/* func_001A53A0 (0x1A53A0): give the LO its own LOROOT if it has none: a record allocated from the slot heap
 * D_003E0E1C (func_0011CCC0) whose first field points back at the LO. */
#include "so.h"
#include "slotheap.h"

typedef struct LOROOT {
    /* 0x00 */ LO *plo;
    /* 0x04 */ DLE dle;
    /* 0x0c */ DLE dleBusy;
} LOROOT;

LOROOT *func_0011CCC0(SLOTHEAP *pslotheap);   /* allocate one slot */
extern SLOTHEAP D_003E0E1C;

void func_001A53A0(LO *plo)
{
    LOROOT *ploroot;

    if (plo->ploroot == NULL) {
        ploroot = func_0011CCC0(&D_003E0E1C);
        plo->ploroot = ploroot;
        ploroot->plo = plo;
    }
}
