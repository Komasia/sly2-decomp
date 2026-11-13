/* class: the breakables (SafeHouse breakable.cpp PevCurrent, orig 0x001BBE68: the current event (0x10 bytes each from
 * +0x164), or null when none is valid). */
struct BRKEV {
    /* 0x0 */ int an[4];
};
struct BREAKABLE {
    /* 0x000 */ char pad0[0x15c];
    /* 0x15c */ int ievCur;
    /* 0x160 */ int cev;
    /* 0x164 */ struct BRKEV *aev;
};
int func_001BBE18(struct BREAKABLE *pbrk);

struct BRKEV *func_001BBE68(struct BREAKABLE *pbrk)
{
    if (func_001BBE18(pbrk) == 0) {
        return 0;
    }
    return &pbrk->aev[pbrk->ievCur];
}
