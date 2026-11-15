/* IRowEnd (SafeHouse shop.cpp): the end of the shop's visible rows - first + D_002C35B4 (6 rows); with the flag
 * D_003DA570 (0 in the game, SafeHouse) one less when first > 0 and one less again when rows remain below. */
extern int D_002C35B4;                /* the visible row count */
extern int D_003DA570;
struct SHOP {                         /* field: SafeHouse port (shop.cpp SHOP) */
    /* 0x000 */ char pad0[0x48];
    /* 0x048 */ int crow;
    /* 0x04c */ char pad4C[0x250 - 0x4C];
    /* 0x250 */ int irowFirst;
};

// name: SafeHouse port (IRowEnd)
int IRowEnd__FP4SHOP(struct SHOP *pshop)
{
    int irowEnd = pshop->irowFirst + D_002C35B4;
    if (D_003DA570) {
        irowEnd -= (pshop->irowFirst > 0);
        irowEnd -= (irowEnd < pshop->crow);
    }
    return irowEnd;
}
