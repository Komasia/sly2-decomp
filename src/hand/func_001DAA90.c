/* UpdateGadgetMenu (SafeHouse shop.cpp, the gadget menu D_003DA0F0's update): with the menu open for a character
 * and the focus: Triangle (0x10) during a message, or no player (class 0x34), closes it; the stick moves the
 * selection; the other face buttons (0x7E8) explain the selected gadget (text 0x31 with entry bit 1, else 0xE2);
 * each of the three assign buttons (D_002C3258) puts an owned gadget with bit 1 in that ability slot (sound 0x34),
 * else says why (0x32 not owned, 0x33 no bit 1). */
#define GRFGADGET_1 1                 /* set elsewhere (meaning not checked) */
#define GRFGADGET_Owned 4             /* UpdateGadgetFlags: FPowerupOwned (bit 2 is FItemOpen, open) */
typedef struct { char pad[0x1C]; int grf; } GADGETENT;   /* field: SafeHouse port */
typedef struct GADGETMENU {           /* field: SafeHouse port (shop.cpp) */
    /* 0x00 */ char pad[0x10];
    /* 0x10 */ void *pjoy;            /* the pad while it has the focus */
    /* 0x14 */ char pad14[0x24 - 0x14];
    /* 0x24 */ void *ploScreen;
    /* 0x28 */ char pad28[0x30 - 0x28];
    /* 0x30 */ int msg;               /* a message shown */
    /* 0x34 */ char pad34[0x40 - 0x34];
    /* 0x40 */ int ichar;             /* -1: closed */
    /* 0x44 */ char pad44[4];
    /* 0x48 */ int key;               /* the gadget selected */
} GADGETMENU;
extern struct G g_sw;
extern int D_002C3258[];             /* the three ability slot buttons */
void func_001DA808(GADGETMENU *);
int GrfbtnTakePressedJoy(void *, int) asm("GrfbtnTakePressedJoy__FP6JOYPS2Ui");
void *PloPlayerPo__FP2SW(struct G *);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *, int);
void SetGadgetMenu__FPvi(GADGETMENU *, int);
void UpdateShopStick__FP4SHOP(GADGETMENU *);
GADGETENT *func_001DAE20(GADGETMENU *pmenu, int key);   /* the entry of a gadget */
void SetShopMsg__FP4SHOPii(GADGETMENU *, int, int);
void *PsndNewPlain__Fi(int);
void SetSource__4CSndPv(void *, int);
void SetActorAbilitySlot__FP5ACTORii(void *, int, int);
// name: SafeHouse port (UpdateGadgetMenu)
void UpdateGadgetMenu__FP2SW(GADGETMENU *pmenu)
{
    void *pplayer;
    GADGETENT *pent;
    int islot;
    func_001DA808(pmenu);
    if (pmenu->ploScreen == 0)
        return;
    if (pmenu->ichar == -1)
        return;
    if (pmenu->pjoy == 0)
        return;
    if (pmenu->msg && GrfbtnTakePressedJoy(pmenu->pjoy, 0x10)) {
        SetGadgetMenu__FPvi(pmenu, -1);
        return;
    }
    pplayer = PloPlayerPo__FP2SW(&g_sw);
    if (pplayer == 0 || !FIsBasicDerivedFrom__FP5BASIC3CID(pplayer, 0x34)) {
        SetGadgetMenu__FPvi(pmenu, -1);
        return;
    }
    UpdateShopStick__FP4SHOP(pmenu);
    if (GrfbtnTakePressedJoy(pmenu->pjoy, 0x7E8)) {
        pent = func_001DAE20(pmenu, pmenu->key);
        if (pent == 0 || !(pent->grf & GRFGADGET_1))
            SetShopMsg__FP4SHOPii(pmenu, 1, 0xE2);
        else
            SetShopMsg__FP4SHOPii(pmenu, 1, 0x31);
    }
    for (islot = 0; islot < 3; islot++) {
        if (!GrfbtnTakePressedJoy(pmenu->pjoy, D_002C3258[islot]))
            continue;
        pent = func_001DAE20(pmenu, pmenu->key);
        if (pent == 0 || !(pent->grf & GRFGADGET_Owned)) {
            SetShopMsg__FP4SHOPii(pmenu, 1, 0x32);
        } else if (!(pent->grf & GRFGADGET_1)) {
            SetShopMsg__FP4SHOPii(pmenu, 1, 0x33);
        } else {
            SetSource__4CSndPv(PsndNewPlain__Fi(0x34), 0);
            SetActorAbilitySlot__FP5ACTORii(pplayer, islot, pmenu->key);
        }
    }
}
