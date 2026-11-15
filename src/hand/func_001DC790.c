/* class: SHOP (a text callback of the shop's screen object): the name of the item on visible row irow (the item
 * table's text id +0x14, localized; empty when none). */
#define CITEM 0x2B
struct SHOPROW { int item; int idIcon; };   /* field: SafeHouse port */
struct SHOP {                               /* D_003DA150 (field: SafeHouse port, shop.cpp SHOP) */
    /* 0x000 */ char pad[0x4C];
    /* 0x04c */ struct SHOPROW arow[0x40];
    /* 0x24c */ int isel;
    /* 0x250 */ int irowFirst;
};
extern struct SHOP D_003DA150;
struct ITEM { int a[5]; int idName; int b[2]; };   /* the item table (SafeHouse shop.cpp: +0x14 its name) */
extern struct ITEM D_002BCD00[];
extern struct G g_sw;
void *func_0013E368(struct G *psw, int id);   /* a localized text */
void s1_strcpy(char *pchDst, void *pchSrc) asm("strcpy");

void func_001DC790(char *pch, int irow)
{
    struct SHOP *pshop = &D_003DA150;
    unsigned int item = pshop->arow[pshop->irowFirst + irow].item;
    int idName = -1;
    if (item < CITEM)
        idName = D_002BCD00[item].idName;
    if (idName != -1)
        s1_strcpy(pch, func_0013E368(&g_sw, idName));
    else
        *pch = 0;
}
