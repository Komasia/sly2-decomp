struct CRef {
    int m_tagk;
    int m_tag;
    CRef() { m_tagk = -1; }
    CRef(int n) { m_tagk = 0x15; m_tag = n; }
    CRef(const CRef &);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &);
    void Decref();
};
/* UpdateShop (SafeHouse shop.cpp): while the shop is open and has the pad: Triangle closes it, or only withdraws a
 * pending buy question; Cross on the buy page asks to buy the selected item (0x34, or 0x35 when the coins do not
 * cover it) and, when asked already, buys it (coins paid, item acquired, rows rebuilt, players told); on the sell
 * page it sells one of the selected loot for its value; Square switches pages; then the stick (not while a
 * question is pending) and the look. */
#define BTN_TRIANGLE 0x10
#define BTN_CROSS 0x40               /* Sly 1 joy.h PAD_ values */
#define BTN_SQUARE 0x80
struct ITEM { int use, kind, cost; int pad[5]; };   /* the item table */
struct LOOT { int nValue, x4, x8; };                /* the loot table */
struct SHOP {                                       /* field: SafeHouse port (shop.cpp SHOP) */
    /* 0x000 */ char pad0[0x10];
    /* 0x010 */ void *pjoy;
    /* 0x014 */ char pad14[0x30 - 0x14];
    /* 0x030 */ int msg;                            /* -1 none, 0 a question (the buy asked), 1 a message */
    /* 0x034 */ char pad34[0x40 - 0x34];
    /* 0x040 */ int page;                           /* 0 buy, 1 sell */
    /* 0x044 */ char pad44[0x254 - 0x44];
    /* 0x254 */ int itemBuy;
    /* 0x258 */ int itemSell;
};
extern "C" {
extern ITEM D_002BCD00[];
extern LOOT D_002C3288[];
extern char g_game[];
extern char g_sw[];
extern char D_002A79A0[], D_002A79D0[], D_002A79D8[];   /* "%d", "loot", "mplootkc" */
void func_001DA808(SHOP *);
int GrfbtnTakePressedJoy(void *, int) asm("GrfbtnTakePressedJoy__FP6JOYPS2Ui");
void func_001DC260(SHOP *pshop, int page);   /* SetShopPage */
int func_00161798(void *pgame);          /* the coins (SafeHouse CCoins) */
void func_001617E0(void *pgame, int ccoin);   /* set the coins (SafeHouse SetCoins) */
void SetShopMsg(SHOP *, int, int) asm("SetShopMsg__FP4SHOPii");
void func_001DAF38(int item, int fAcquired);
void BuildShopList(SHOP *) asm("BuildShopList__FP4SHOP");
void *PsndNewPlain(int) asm("PsndNewPlain__Fi");
void SetSource(void *, int) asm("SetSource__4CSndPv");
void NotifyPlayersPowerups(void *) asm("NotifyPlayersPowerups__Fv");
void sprintf(char *, const char *, ...) asm("sprintf");
CRef func_001D8A38(const char *, ...);
CRef SetProgressPoCurrent(const CRef &, const char *, ...) asm("SetProgressPoCurrent__FP4CRefPci");
void UpdateShopStick(SHOP *) asm("UpdateShopStick__FP4SHOP");
void UpdateShopLook(SHOP *) asm("UpdateShopLook__FP4SHOP");
}
// name: SafeHouse port (UpdateShop)
extern "C" void UpdateShop__FP2SW(SHOP *pshop)
{
    func_001DA808(pshop);
    if (pshop->page == -1)
        return;
    if (!pshop->pjoy)
        return;
    if (pshop->msg && GrfbtnTakePressedJoy(pshop->pjoy, BTN_TRIANGLE)) {
        func_001DC260(pshop, -1);
        return;
    }
    switch (pshop->page) {
    case 0:
        if (GrfbtnTakePressedJoy(pshop->pjoy, BTN_CROSS)) {
            if (pshop->itemBuy != -1) {
                int cost = D_002BCD00[pshop->itemBuy].cost;
                int ccoin = func_00161798(g_game);
                if (!pshop->msg) {
                    SetShopMsg(pshop, -1, -1);
                    func_001617E0(g_game, ccoin - cost);
                    func_001DAF38(pshop->itemBuy, 1);
                    BuildShopList(pshop);
                    SetSource(PsndNewPlain(0x29), 0);
                    NotifyPlayersPowerups(g_sw);
                } else if (ccoin >= cost) {
                    SetShopMsg(pshop, 0, 0x34);
                } else {
                    SetShopMsg(pshop, 1, 0x35);
                }
            } else {
                SetSource(PsndNewPlain(0x36), 0);
            }
        }
        break;
    case 1:
        if (GrfbtnTakePressedJoy(pshop->pjoy, BTN_CROSS)) {
            if (pshop->itemSell == -1) {
                SetSource(PsndNewPlain(0x36), 0);
            } else {
                CRef refCount;
                char achLoot[32];
                sprintf(achLoot, D_002A79A0, pshop->itemSell);
                refCount = func_001D8A38(D_002A79D0, D_002A79D8, achLoot, 0);
                if (refCount.m_tag > 0) {
                    SetProgressPoCurrent(CRef(refCount.m_tag - 1), D_002A79D0, D_002A79D8, achLoot, 0);
                    func_001617E0(g_game, func_00161798(g_game) + D_002C3288[pshop->itemSell].nValue);
                    BuildShopList(pshop);
                    SetSource(PsndNewPlain(0x29), 0);
                }
            }
        }
        break;
    }
    if (!pshop->msg && GrfbtnTakePressedJoy(pshop->pjoy, BTN_TRIANGLE))
        SetShopMsg(pshop, -1, -1);
    if (GrfbtnTakePressedJoy(pshop->pjoy, BTN_SQUARE)) {
        SetShopMsg(pshop, -1, -1);
        func_001DC260(pshop, pshop->page == 0);
    }
    if (pshop->msg)
        UpdateShopStick(pshop);
    UpdateShopLook(pshop);
}
