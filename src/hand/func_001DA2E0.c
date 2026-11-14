/* class: PROMPT, a HUD widget (SafeHouse hudwidget.cpp, orig 0x001DA320 (the reset) / 0x001DA2E0): its screen object
 * 0x371 found. */
struct LO;
struct SW;
extern struct SW g_sw;
struct PROMPT {
    /* 0x00 */ char pad0[0x28];
    /* 0x28 */ struct LO *ploScreen;
};
struct LO *PloFindSwNearest__FP2LO3OIDii(struct SW *psw, int grf, int oid, int n);

void func_001DA2E0(struct PROMPT *pprompt)
{
    pprompt->ploScreen = PloFindSwNearest__FP2LO3OIDii(&g_sw, 0x405, 0x371, 0);
}
