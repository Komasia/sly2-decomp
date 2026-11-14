/* class: SHOP (SafeHouse shop.h InitShop, orig 0x001DB7F0: the reset): the base 0x1DA7B0, then 0x1DB820. */
struct SHOP;
void func_001DA7B0(struct SHOP *pshop);
void func_001DB820(struct SHOP *pshop);

void func_001DB7F0(struct SHOP *pshop)
{
    func_001DA7B0(pshop);
    func_001DB820(pshop);
}
