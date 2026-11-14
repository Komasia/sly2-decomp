/* class: SHOP (SafeHouse shop.cpp / hudwidget.cpp, 0x1DA7D0): no state (+0x28 -1, the real time +0x2C), no message. */
#include "clock.h"
struct SHOP {
    /* 0x00 */ char pad0[0x28];
    /* 0x28 */ int state;
    /* 0x2c */ float tState;
};
void SetShopMsg__FP4SHOPii(struct SHOP *pshop, int n1, int n2);

void func_001DA7D0(struct SHOP *pshop)
{
    pshop->state = -1;
    pshop->tState = g_clock.tReal;
    SetShopMsg__FP4SHOPii(pshop, -1, -1);
}
