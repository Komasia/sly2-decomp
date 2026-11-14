/* A HUD dialog (SafeHouse menu.h / shop.h: the card dialogs' and the shop's object, 0x1DA770): its screen object by
 * the oid +0x20. */
struct LO;
struct SW;
extern struct SW g_sw;
struct DIALOG {
    /* 0x00 */ char pad0[0x20];
    /* 0x20 */ int oid;
    /* 0x24 */ struct LO *ploScreen;
};
struct LO *PloFindSwNearest__FP2LO3OIDii(struct SW *psw, int grf, int oid, int n);

void func_001DA770(struct DIALOG *pdialog)
{
    pdialog->ploScreen = PloFindSwNearest__FP2LO3OIDii(&g_sw, 5, pdialog->oid, 0);
}
