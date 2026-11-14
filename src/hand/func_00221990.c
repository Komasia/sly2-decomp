/* A camera policy's constructor (SafeHouse cplcy.cpp: one of the constructors 0x14FD68, 0x221990, ..): the base
 * 0x14FCA8, then its vtable D_002DB858. */
#include "vtbl.h"
struct CPLCY {
    /* 0x00 */ char pad0[0xc];
    /* 0x0c */ VTENT *pvt;
};
extern VTENT D_002DB858[];   /* its vtable */
void func_0014FCA8(struct CPLCY *pcplcy);

struct CPLCY *func_00221990(struct CPLCY *pcplcy)
{
    func_0014FCA8(pcplcy);
    pcplcy->pvt = D_002DB858;
    return pcplcy;
}
