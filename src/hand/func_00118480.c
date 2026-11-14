/* class: a CBinaryInputStream over one memory block (vtable 0x2CA5A0: Fill 0x1184E8, Close = the base's 0x1177F0;
 * built by 0x1CAEC8): its constructor - the base constructor, then the subclass vtable (vptr at +0x30). */
#include "so.h"

typedef struct BISMEM {
    /* 0x00 */ char bis[0x30];   /* CBinaryInputStream fields (bis.h) */
    /* 0x30 */ VTE *pvt;
    /* 0x34 */ int cbBlock;      /* the block not yet handed out by Fill */
    /* 0x38 */ void *pbBlock;
} BISMEM;

void __18CBinaryInputStream(void *pbis);
extern VTE D_002CA5A0[];

BISMEM *func_00118480(BISMEM *pbis)
{
    __18CBinaryInputStream(pbis);
    pbis->pvt = D_002CA5A0;
    return pbis;
}
