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
struct REC { int a, b, x8; int pad[5]; };
struct REC12 { int x0, x4, x8; };
struct OBJ {
    char pad0[0x10];
    void *x10;
    char pad14[0x30 - 0x14];
    int x30;
    char pad34[0x40 - 0x34];
    int x40;
    char pad44[0x254 - 0x44];
    int x254;
    int x258;
};
extern "C" {
extern REC D_002BCD00[];
extern REC12 D_002C3288[];
extern char g_game[];
extern char g_sw[];
extern char D_002A79A0[], D_002A79D0[], D_002A79D8[];
void func_001DA808(OBJ *);
int func_00187D80(void *, int);
void func_001DC260(OBJ *, int);
int func_00161798(void *);
void func_001617E0(void *, int);
void SetShopMsg(OBJ *, int, int) asm("SetShopMsg__FP4SHOPii");
void func_001DAF38(int, int);
void BuildShopList(OBJ *) asm("BuildShopList__FP4SHOP");
void *PsndNewPlain(int) asm("PsndNewPlain__Fi");
void SetSource(void *, int) asm("SetSource__4CSndPv");
void NotifyPlayersPowerups(void *) asm("NotifyPlayersPowerups__Fv");
void fiprintf(char *, const char *, ...) asm("fiprintf");
CRef func_001D8A38(const char *, ...);
CRef SetProgressPoCurrent(const CRef &, const char *, ...) asm("SetProgressPoCurrent__FP4CRefPci");
void UpdateShopStick(OBJ *) asm("UpdateShopStick__FP4SHOP");
void UpdateShopLook(OBJ *) asm("UpdateShopLook__FP4SHOP");
}
// name: SafeHouse port (UpdateShop)
extern "C" void UpdateShop__FP2SW(OBJ *p)
{
    func_001DA808(p);
    if (p->x40 == -1)
        return;
    if (!p->x10)
        return;
    if (p->x30 && func_00187D80(p->x10, 0x10)) {
        func_001DC260(p, -1);
        return;
    }
    switch (p->x40) {
    case 0:
        if (func_00187D80(p->x10, 0x40)) {
            if (p->x254 != -1) {
                int cost = D_002BCD00[p->x254].x8;
                int have = func_00161798(g_game);
                if (!p->x30) {
                    SetShopMsg(p, -1, -1);
                    func_001617E0(g_game, have - cost);
                    func_001DAF38(p->x254, 1);
                    BuildShopList(p);
                    SetSource(PsndNewPlain(0x29), 0);
                    NotifyPlayersPowerups(g_sw);
                } else if (have >= cost) {
                    SetShopMsg(p, 0, 0x34);
                } else {
                    SetShopMsg(p, 1, 0x35);
                }
            } else {
                SetSource(PsndNewPlain(0x36), 0);
            }
        }
        break;
    case 1:
        if (func_00187D80(p->x10, 0x40)) {
            if (p->x258 == -1) {
                SetSource(PsndNewPlain(0x36), 0);
            } else {
                CRef r;
                char buf[32];
                fiprintf(buf, D_002A79A0, p->x258);
                r = func_001D8A38(D_002A79D0, D_002A79D8, buf, 0);
                if (r.m_tag > 0) {
                    SetProgressPoCurrent(CRef(r.m_tag - 1), D_002A79D0, D_002A79D8, buf, 0);
                    func_001617E0(g_game, func_00161798(g_game) + D_002C3288[p->x258].x0);
                    BuildShopList(p);
                    SetSource(PsndNewPlain(0x29), 0);
                }
            }
        }
        break;
    }
    if (!p->x30 && func_00187D80(p->x10, 0x10))
        SetShopMsg(p, -1, -1);
    if (func_00187D80(p->x10, 0x80)) {
        SetShopMsg(p, -1, -1);
        func_001DC260(p, p->x40 == 0);
    }
    if (p->x30)
        UpdateShopStick(p);
    UpdateShopLook(p);
}
