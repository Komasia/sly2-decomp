/* class: SHOP's constructor (SafeHouse shop.cpp, module 0x1DAA08..): the base 0x1DA728, its vtable D_002D8568, then
 * 0x1DAA78. */
#include "vtbl.h"
struct SHOP {
    /* 0x00 */ char pad0[0xc];
    /* 0x0c */ VTENT *pvt;
};
extern VTENT D_002D8568[];   /* its vtable */
struct SHOP *func_001DA728(struct SHOP *pshop);   /* the base constructor */
void func_001DAA78(struct SHOP *pshop);

struct SHOP *func_001DAA08(struct SHOP *pshop)
{
    func_001DA728(pshop);
    pshop->pvt = D_002D8568;
    func_001DAA78(pshop);
    return pshop;
}
