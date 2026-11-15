/* class: HUD menu widget (SafeHouse shop.cpp / hudwidget.cpp, 0x1DA7D0): no stick direction (+0x28 -1, its time
 * +0x2C the real time), no message. */
#include "clock.h"
struct SHOP {
    /* 0x00 */ char pad0[0x28];
    /* 0x28 */ int dir;               /* field: SafeHouse port */
    /* 0x2c */ float tDir;            /* field: SafeHouse port */
};
void SetShopMsg__FP4SHOPii(struct SHOP *pshop, int msg, int idMsg);

void func_001DA7D0(struct SHOP *pshop)
{
    pshop->dir = -1;
    pshop->tDir = g_clock.tReal;
    SetShopMsg__FP4SHOPii(pshop, -1, -1);
}
