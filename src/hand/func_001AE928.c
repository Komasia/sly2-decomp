/* class: MENU, the paged menu (SafeHouse menu.h InitMenu, orig 0x001AE928: after a world load - its screen object
 * 0x370, no page, state 0). */
struct LO;
struct SW;
extern struct SW g_sw;
struct MENU {
    /* 0x000 */ char pad0[0x20];
    /* 0x020 */ struct LO *ploScreen;
    /* 0x024 */ char pad24[0x1e8 - 0x24];
    /* 0x1e8 */ int state;   /* field: SafeHouse port */
    /* 0x1ec */ int n1EC;
};
struct LO *PloFindSwNearest__FP2LO3OIDii(struct SW *psw, int grf, int oid, int n);

void func_001AE928(struct MENU *pmenu)
{
    pmenu->ploScreen = PloFindSwNearest__FP2LO3OIDii(&g_sw, 0x405, 0x370, 0);
    pmenu->n1EC = -1;
    pmenu->state = 0;
}
