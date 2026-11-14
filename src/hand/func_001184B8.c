/* class: a CBinaryInputStream over one memory block (vtable 0x2CA5A0; see 0x118480): its destructor (bit 0 of the
 * flags: delete the object too). */
#include "so.h"

typedef struct BISMEM {
    /* 0x00 */ char bis[0x30];   /* CBinaryInputStream fields (bis.h) */
    /* 0x30 */ VTE *pvt;
} BISMEM;

void __builtin_delete(void *pv);
extern VTE D_002CA5A0[];

void func_001184B8(BISMEM *pbis, int grfDelete)
{
    pbis->pvt = D_002CA5A0;
    if (grfDelete & 1) {
        __builtin_delete(pbis);
    }
}
