/* A camera policy's constructor (SafeHouse cplcy.cpp: one of the constructors 0x14FD68, 0x221990, 0x14FDE0, 0x12E760, ..):
 * the base 0x14FCA8, then its vtable D_002CAB90. */
#include "vtbl.h"
struct CPLCY {
    /* 0x00 */ char pad0[0xc];
    /* 0x0c */ VTENT *pvt;
};
extern VTENT D_002CAB90[];   /* its vtable */
void func_0014FCA8(struct CPLCY *pcplcy);

struct CPLCY *func_0012E760(struct CPLCY *pcplcy)
{
    func_0014FCA8(pcplcy);
    pcplcy->pvt = D_002CAB90;
    return pcplcy;
}
