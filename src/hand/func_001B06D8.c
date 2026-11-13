/* A paged menu entry's action (SafeHouse menu.cpp case 0x1B06D8: a yes / no page): the page replaced with the entry's
 * +0x8 / +0xC, then the entry's flag 2. */
struct MENU;
struct MENUENT {
    /* 0x00 */ char pad0[8];
    /* 0x08 */ int idPage;
    /* 0x0c */ void *pv;
    /* 0x10 */ char pad10[0x1c - 0x10];
    /* 0x1c */ int grf;
};
extern struct MENU D_003D9ED0;   /* the paged menu */
void ReplacePage__FP4MENUiPv(struct MENU *pmenu, int idPage, void *pv);

void func_001B06D8(struct MENUENT *pent)
{
    ReplacePage__FP4MENUiPv(&D_003D9ED0, pent->idPage, pent->pv);
    if (pent != 0) {
        pent->grf |= 2;
    }
}
