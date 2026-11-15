#include "clock.h"
/* SetShopDir (SafeHouse shop.cpp, the shop's vtable entry 14): the stick's direction (eighths of a turn from the
 * right, -1 none) changes: right shows page 1, left page 0; up-ish (1..3) selects the row above, down-ish (5..7) the
 * row below, with a click (sound 0x35) or a bump at the end (0x36). */
typedef struct SHOP {                 /* field: SafeHouse port (shop.cpp SHOP) */
    /* 0x000 */ char pad[0x28];
    /* 0x028 */ int dir;
    /* 0x02c */ float tDir;
    /* 0x030 */ char pad30[0x48 - 0x30];
    /* 0x048 */ int crow;
    /* 0x04c */ char pad4c[0x24C - 0x4C];
    /* 0x24c */ int isel;
} SHOP;
#define DIR_Right 0
#define DIR_Left 4
void func_001DC260(SHOP *pshop, int page);   /* SafeHouse SetShopPage */
void SelectShopRow__FP4SHOPi(SHOP *, int);
void *PsndNewPlain__Fi(int);
void SetSource__4CSndPv(void *, int);
// name: SafeHouse port (SetShopDir)
void SetShopDir__FP4SHOPi(SHOP *pshop, unsigned int dir)
{
    if (dir == pshop->dir)
        return;
    pshop->dir = dir;
    pshop->tDir = g_clock.tReal;
    switch (dir) {
    case DIR_Right:
        func_001DC260(pshop, 1);
        break;
    case DIR_Left:
        func_001DC260(pshop, 0);
        break;
    case 1:
    case 2:
    case 3:
        if (pshop->isel > 0) {
            SelectShopRow__FP4SHOPi(pshop, pshop->isel - 1);
            SetSource__4CSndPv(PsndNewPlain__Fi(0x35), 0);
        } else {
            SetSource__4CSndPv(PsndNewPlain__Fi(0x36), 0);
        }
        break;
    case 5:
    case 6:
    case 7:
        if (pshop->isel < pshop->crow - 1) {
            SelectShopRow__FP4SHOPi(pshop, pshop->isel + 1);
            SetSource__4CSndPv(PsndNewPlain__Fi(0x35), 0);
        } else {
            SetSource__4CSndPv(PsndNewPlain__Fi(0x36), 0);
        }
        break;
    }
}
