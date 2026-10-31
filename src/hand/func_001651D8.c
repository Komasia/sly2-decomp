struct G;
struct Q { char pad[0x10]; int f10; int f14; int f18; };
extern struct G D_003DD490;
extern struct Q g_game;
void *func_0015E938(struct G *pg, int kind, int oid, void *owner);
void func_00165E10(struct G *pg, void *p);
void func_00165538(void *p);
void func_0022B490(struct G *pg, int n, int a, int b, int c, int d);
void func_001651D8(void *pv, int n, int oid)
{
    struct G *pg = &D_003DD490;
    void *p = func_0015E938(pg, 0x105, oid, 0);
    if (p) {
        func_00165E10(pg, p);
        func_00165538(p);
    } else {
        g_game.f10 = -1;
        g_game.f14 = -1;
        g_game.f18 = oid;
        func_0022B490(pg, n, 0x189, -1, 8, -1);
    }
}
