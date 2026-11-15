/* class: SHOP (a text callback of the shop's screen object): the name of the loot on visible row irow of the sell
 * page (the loot table's text id, localized), followed by its count (D_002A7A30) when the player has 2 or more
 * (progress "loot" "mplootkc" "<n>"); empty when none. */
struct CRef {
    int m_tagk;
    int m_tag;
    CRef() { m_tagk = -1; }
    CRef(const CRef &);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &);
    void Decref();
};
struct ENT { int n; int a; };
struct TBL {
    char pad[0x4C];
    ENT ae[0x40];
    int i;
    int first;
};
struct REC { char *name; int ids; int pad; };
struct G;
extern G g_sw;
extern TBL D_003DA150;
extern REC D_002C3288[];
extern char D_002A79A0[];
extern char D_002A79D0[];
extern char D_002A79D8[];
extern char D_002A7A30[];
extern "C" int sprintf(char *, const char *, ...) asm("sprintf");
extern "C" char *s1_strcpy(char *, const char *) asm("strcpy");
extern "C" CRef func_001D8A38(const char *, ...);
char *func_0013E368(G *, int);
extern "C" void func_001DC890(char *pch, int irow)
{
    int ids = -1;
    int cloot = 0;
    unsigned int loot = D_003DA150.ae[D_003DA150.first + irow].n;
    if (loot < 0x40) {
        CRef ref;
        char achLoot[0x20];
        sprintf(achLoot, D_002A79A0, loot);
        ref = func_001D8A38(D_002A79D0, D_002A79D8, achLoot, 0);
        cloot = ref.m_tag;
        ids = D_002C3288[loot].ids;
    }
    if (ids != -1) {
        s1_strcpy(pch, func_0013E368(&g_sw, ids));
        if (cloot >= 2)
            sprintf(pch, D_002A7A30, pch, cloot);
    } else {
        *pch = 0;
    }
}
