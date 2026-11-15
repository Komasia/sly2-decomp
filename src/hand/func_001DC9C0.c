/* class: SHOP (a text callback of the shop's screen object): the value of the loot on visible row irow ("%d", from
 * the loot table D_002C3288; empty when none). */
#define CLOOT 0x40
struct SHOPROW { int item; int idIcon; };   /* field: SafeHouse port */
struct SHOP {                               /* D_003DA150 (field: SafeHouse port, shop.cpp SHOP) */
    /* 0x000 */ char pad[0x4C];
    /* 0x04c */ struct SHOPROW arow[0x40];
    /* 0x24c */ int isel;
    /* 0x250 */ int irowFirst;
};
extern struct SHOP D_003DA150;
struct LOOT { int nValue; int b[2]; };
extern struct LOOT D_002C3288[];
extern char D_002A79A0[];                   /* "%d" */
void sprintf(char *pch, char *pchzFormat, int n);

void func_001DC9C0(char *pch, int irow)
{
    struct SHOP *pshop = &D_003DA150;
    unsigned int loot = pshop->arow[pshop->irowFirst + irow].item;
    int nValue = 0;
    if (loot < CLOOT)
        nValue = D_002C3288[loot].nValue;
    if (nValue)
        sprintf(pch, D_002A79A0, nValue);
    else
        *pch = 0;
}
