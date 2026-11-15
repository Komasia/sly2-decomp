struct CRef {
    int m_tagk;
    int m_tag;
    CRef() { m_tagk = -1; }
    CRef(const CRef &);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &);
    void Decref();
};
/* BuildShopList (SafeHouse shop.cpp, orig 0x1DBD10): fill the shop's rows for its page - buy (0): every item from 7
 * on that is open and not yet owned; sell (1): every loot kind the player has (progress "loot" "mplootkc" "<n>"
 * nonzero) - then select the current row again. */
#define CITEM 0x2B
#define CLOOT 0x40
#define CSHOPROW 0x40
struct SHOPROW { int item; int idIcon; };   /* field: SafeHouse port */
struct SHOP {                               /* field: SafeHouse port (shop.cpp SHOP) */
    /* 0x000 */ char pad[0x40];
    /* 0x040 */ int page;
    /* 0x044 */ int pad44;
    /* 0x048 */ unsigned int crow;
    /* 0x04c */ SHOPROW arow[CSHOPROW];
    /* 0x24c */ int isel;
};
extern char D_002A79A0[];
extern char D_002A79D0[];   /* "loot" */
extern char D_002A79D8[];   /* "mplootkc" */
extern "C" int sprintf(char *, const char *, ...) asm("sprintf");
extern "C" CRef func_001D8A38(const char *, ...);
extern "C" int FItemOpen__Fi(int);
extern "C" int FPowerupOwned__Fi(int);
extern "C" void SelectShopRow(SHOP *, int) asm("SelectShopRow__FP4SHOPi");
// name: SafeHouse port (BuildShopList)
extern "C" void BuildShopList__FP4SHOP(SHOP *pshop)
{
    {
        int j;
        for (j = 0; j < (int)pshop->crow; j++)
            pshop->arow[j].item = -1;
    }
    pshop->crow = 0;
    switch (pshop->page) {
    case 0: {
        int i;
        for (i = 7; i < CITEM; i++) {
            if (!FItemOpen__Fi(i))
                continue;
            if (FPowerupOwned__Fi(i))
                continue;
            if (pshop->crow > CSHOPROW)
                break;
            pshop->arow[pshop->crow++].item = i;
        }
        break;
    }
    case 1: {
        int i;
        for (i = 0; i < CLOOT; i++) {
            CRef ref;
            char achLoot[0x20];
            sprintf(achLoot, D_002A79A0, i);
            ref = func_001D8A38(D_002A79D0, D_002A79D8, achLoot, 0);
            if (ref.m_tag == 0)
                continue;
            if (pshop->crow > CSHOPROW)
                break;
            pshop->arow[pshop->crow++].item = i;
        }
        break;
    }
    }
    SelectShopRow(pshop, pshop->isel);
}
