/* class: SHOP, Job Help's screen (SafeHouse shop.cpp, orig 0x001DCCA0: it pauses the world while its panel is
 * shown): its screen object found, its +0xB0 set. */
struct SCREENOBJ {
    /* 0x00 */ char pad0[0xb0];
    /* 0xb0 */ int fB0;
};
struct DIALOG {
    /* 0x00 */ char pad0[0x24];
    /* 0x24 */ struct SCREENOBJ *ploScreen;
};
void func_001DA770(struct DIALOG *pdialog);

void func_001DCCA0(struct DIALOG *pdialog)
{
    struct SCREENOBJ *pso;
    func_001DA770(pdialog);
    pso = pdialog->ploScreen;
    if (pso != 0) {
        pso->fB0 = 1;
    }
}
