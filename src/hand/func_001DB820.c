/* class: SHOP (SafeHouse shop.cpp): reset the shop's state - no page (its time the real time), no prompt / up / down
 * handles, and all 64 rows empty. */
#include "clock.h"
struct SHOPROW { int id; int idIcon; };   /* field: SafeHouse port */
struct SHOP {                         /* field: SafeHouse port (shop.cpp SHOP) */
    /* 0x000 */ char pad0[0x40];
    /* 0x040 */ int page;
    /* 0x044 */ float tPage;
    /* 0x048 */ int crow;
    /* 0x04c */ struct SHOPROW arow[64];
    /* 0x24c */ char pad24C[0x25C - 0x24C];   /* isel, first, itemBuy, itemSell */
    /* 0x25c */ int idPrompt;
    /* 0x260 */ int idUp;
    /* 0x264 */ int idDown;
};

void func_001DB820(struct SHOP *pshop)
{
    unsigned int irow;
    pshop->page = -1;
    pshop->tPage = g_clock.tReal;
    pshop->idPrompt = -1;
    pshop->idUp = -1;
    pshop->idDown = -1;
    for (irow = 0; irow < 64; irow++) {
        pshop->arow[irow].id = -1;
        pshop->arow[irow].idIcon = -1;
    }
}
