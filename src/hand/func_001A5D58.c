/* func_001A5D58 (0x1A5D58): push a new run record (from the world, func_00210100) onto the LO's run list
 * LO::plorunFirst and return it. */
#include "so.h"

typedef struct LORUN {
    /* 0x00 */ void *pfn;
    /* 0x04 */ void *pv;
    /* 0x08 */ struct LORUN *plorunNext;
} LORUN;

LORUN *func_00210100(void *psw);
extern char D_003DD490[];   /* the world (SW) */

LORUN *func_001A5D58(LO *plo)
{
    LORUN *plorun = func_00210100(D_003DD490);

    plorun->plorunNext = (LORUN *)plo->plorunFirst;
    plo->plorunFirst = plorun;
    return plorun;
}
