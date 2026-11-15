/* class: HUD menu widget (SafeHouse shop.cpp): the base update (empty 0x1D9870), then the message is cleared once its
 * time (+0x34, real time) is up. */
#include "clock.h"
struct SHOP {
    /* 0x00 */ char pad0[0x34];
    /* 0x34 */ float tMsg;            /* field: SafeHouse port */
};
void func_001D9870(struct SHOP *pshop);
void SetShopMsg__FP4SHOPii(struct SHOP *pshop, int msg, int idMsg);

void func_001DA808(struct SHOP *pshop)
{
    func_001D9870(pshop);
    if (pshop->tMsg <= g_clock.tReal)
        SetShopMsg__FP4SHOPii(pshop, -1, -1);
}
