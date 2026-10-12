/* near: logic matches; target recomputes &D_003DD490 from a hoisted %hi in s4 per block, ours keeps &g in s1 plus hi in s5 (extra s-reg) */
typedef struct CRef { int m_tagk; int m_tag; } CRef;
struct G { char pad[0x3B1C]; void *f3b1c; char pad2[0x3B28 - 0x3B20]; void *f3b28; char pad3[0x3B7C - 0x3B2C]; void *a3b7c[1]; };
struct Q { int a[4]; int f10; int f14; int f18; };
extern struct G D_003DD490;
extern struct Q D_002DEB30;
extern void *D_002DEB4C;
extern char D_003DA530[];
extern char D_002A3828[];
void func_002581C0(CRef *pref, void *a, void *b);
void func_00129EC8(CRef *pref);
int func_001D9880(void *p);
void func_001D54B8(void);
void func_001DD888(void *p);
void *func_00210B98(int n);
void func_0022B490(struct G *pg, void *p, int a, int b, int c, int d);
void func_00165E38(void *pv)
{
    CRef ref;
    float g;
    int n;
    void *ps;
    int m;
    func_002581C0(&ref, D_003DD490.f3b1c, pv);
    g = *(float *)&ref.m_tag;
    func_00129EC8(&ref);
    if (func_001D9880(D_003DA530)) {
        if (g == 0.0f) {
            func_001D54B8();
            func_001DD888(D_003DA530);
            return;
        }
    } else if (g == 0.0f) {
        D_002DEB4C = pv;
        D_002DEB30.f18 = 0x62F;
        D_002DEB30.f14 = -1;
        D_002DEB30.f10 = -1;
        func_0022B490(&D_003DD490, func_00210B98(0), 0x189, -1, 0x48, -1);
        return;
    }
    D_002DEB30.f18 = -1;
    D_002DEB4C = pv;
    D_002DEB30.f10 = -1;
    D_002DEB30.f14 = -1;
    func_002581C0(&ref, D_003DD490.f3b28, pv);
    n = ref.m_tag;
    func_00129EC8(&ref);
    ps = func_00210B98(n);
    m = 0;
    if (D_003DD490.a3b7c[n]) {
        func_002581C0(&ref, D_003DD490.a3b7c[n], pv);
        m = ref.m_tag;
        func_00129EC8(&ref);
    }
    if (m >= 100 || !ps)
        ps = D_002A3828;
    func_0022B490(&D_003DD490, ps, 0x189, -1, 0x40, -1);
}
