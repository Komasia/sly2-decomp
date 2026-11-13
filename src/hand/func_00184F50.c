/* class: CID_13, the hooks (vt slot 7 = InitLo; SafeHouse brx.cpp: the base 0x21D278, then +0xE8 1 (the jump target's
 * grfHook bit), +0x12C 8, +0x130 9 (its sound, SafeHouse sly.cpp)). */
struct HOOK {
    /* 0x000 */ char pad0[0xe8];
    /* 0x0e8 */ int grfHook;
    /* 0x0ec */ char padec[0x100 - 0xec];
    /* 0x100 */ char sub100[0x2c];   /* initialised by 0x182C70 */
    /* 0x12c */ int n12C;
    /* 0x130 */ int n130;
};
void func_0021D278(struct HOOK *phook);   /* the base InitLo (cid 0x12) */
void func_00182C70(void *p);

void func_00184F50(struct HOOK *phook)
{
    func_0021D278(phook);
    func_00182C70(phook->sub100);
    phook->grfHook = 1;
    phook->n12C = 8;
    phook->n130 = 9;
}
