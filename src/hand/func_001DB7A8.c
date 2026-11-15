/* class: SHOP, the shop HUD widget D_003DA150 (SafeHouse shop.cpp): its constructor - the base HUD widget, its vtable
 * D_002D84E8, its screen object 0x378, then its state reset (func_001DB820). */
#define OID_SCREENSHOP 0x378
extern char D_002D84E8[];
struct SHOP {
    /* 0x00 */ int a, b, c;
    /* 0x0c */ void *pvt;
    /* 0x10 */ char pad10[0x10];
    /* 0x20 */ int oidScreen;
};
struct SHOP *func_001DA728(struct SHOP *pshop);   /* the base constructor */
void func_001DB820(struct SHOP *pshop);

struct SHOP *func_001DB7A8(struct SHOP *pshop)
{
    func_001DA728(pshop);
    pshop->pvt = D_002D84E8;
    pshop->oidScreen = OID_SCREENSHOP;
    func_001DB820(pshop);
    return pshop;
}
