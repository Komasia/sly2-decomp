/* class: SHOP (a text callback of the shop's screen object): the cost of the item on visible row irow ("%d";
 * empty when none or free). */
#define CITEM 0x2B
struct SHOPROW { int item; int idIcon; };   /* field: SafeHouse port */
struct SHOP {                               /* D_003DA150 (field: SafeHouse port, shop.cpp SHOP) */
    /* 0x000 */ char pad[0x4C];
    /* 0x04c */ struct SHOPROW arow[0x40];
    /* 0x24c */ int isel;
    /* 0x250 */ int irowFirst;
};
extern struct SHOP D_003DA150;
struct ITEM { int a[2]; int cost; int b[5]; };   /* the item table (SafeHouse shop.cpp: +8 the cost) */
extern struct ITEM D_002BCD00[];
extern char D_002A79A0[];                   /* "%d" */
void sprintf(char *pch, char *pchzFormat, int n);

void func_001DC820(char *pch, int irow)
{
    struct SHOP *pshop = &D_003DA150;
    unsigned int item = pshop->arow[pshop->irowFirst + irow].item;
    int cost = 0;
    if (item < CITEM)
        cost = D_002BCD00[item].cost;
    if (cost)
        sprintf(pch, D_002A79A0, cost);
    else
        *pch = 0;
}
