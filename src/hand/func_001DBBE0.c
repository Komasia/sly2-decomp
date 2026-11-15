/* SelectShopRow (SafeHouse shop.cpp): select row irow of the shop (clamped), scroll so it is visible, and make its
 * item the one to buy / sell; an empty list selects nothing. The message is cleared. */
typedef struct { int item; int idIcon; } SHOPROW;   /* field: SafeHouse port */
typedef struct SHOP {                 /* field: SafeHouse port (shop.cpp SHOP) */
    /* 0x000 */ char pad[0x48];
    /* 0x048 */ int crow;
    /* 0x04c */ SHOPROW arow[64];
    /* 0x24c */ int isel;
    /* 0x250 */ int irowFirst;
    /* 0x254 */ int itemBuy;
    /* 0x258 */ int itemSell;
} SHOP;
extern int D_003DA570;
extern int D_002C35B4;                /* the visible row count */
int IRowEnd__FP4SHOP(SHOP *);
void func_001DA9E8(SHOP *);
static inline int Max(int a, int b) { return a < b ? b : a; }
static inline int Clamp(int n, int lo, int hi)
{
    if (n < lo)
        return lo;
    if (n > hi)
        return hi;
    return n;
}
// name: SafeHouse port (SelectShopRow)
void SelectShopRow__FP4SHOPi(SHOP *pshop, int irow)
{
    if (pshop->crow == 0) {
        pshop->irowFirst = 0;
        pshop->isel = -1;
        pshop->itemBuy = -1;
        pshop->itemSell = -1;
    } else {
        irow = Clamp(irow, 0, pshop->crow - 1);
        pshop->isel = irow;
        if (D_003DA570) {
            if (irow < pshop->irowFirst) {
                pshop->irowFirst = irow;
            } else {
                while (IRowEnd__FP4SHOP(pshop) - 1 < pshop->isel)
                    pshop->irowFirst++;
            }
            if (pshop->irowFirst == 1)
                pshop->irowFirst = 0;
        } else {
            int irowFirst = Clamp(pshop->irowFirst, Max(irow - D_002C35B4 + 1, 0), irow);
            pshop->irowFirst = irowFirst;
        }
        pshop->itemBuy = pshop->arow[pshop->isel].item;
        pshop->itemSell = pshop->arow[pshop->isel].item;
    }
    func_001DA9E8(pshop);
}
