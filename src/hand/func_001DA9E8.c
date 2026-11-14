/* class: the shop / gadget menu HUD widgets (SetShopMsg's; StepGadget / SelectShopRow / 0x1DCE90 call it): no message (SetShopMsg -1, -1). */
typedef struct SHOP SHOP;
void SetShopMsg__FP4SHOPii(SHOP *pshop, int n1, int n2);

void func_001DA9E8(SHOP *pshop)
{
    SetShopMsg__FP4SHOPii(pshop, -1, -1);
}
