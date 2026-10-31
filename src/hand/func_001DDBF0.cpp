struct CRef {
    int m_tagk;
    union { int m_tag; float m_g; };
    CRef() { m_tagk = -1; }
    CRef(const CRef &);
    ~CRef() { Decref(); }
    void Decref();
};
struct G { char pad[0x3B1C]; void *x3B1C; };
struct H { char pad[0x100C]; int x100C; int x1010; };
struct I { char pad[0xFD54]; void *xFD54; };
extern G D_003DD490;
extern H g_joy;
extern I D_002E65E0;
extern char D_002A7A70[];
extern "C" char *func_0021ED58(char *, const char *);
extern "C" char *func_0021EDA0(char *, const char *);
extern "C" int func_001A2C98(void);
char *func_0013E368(G *, int);
CRef func_002581C0(void *, void *);
extern "C" void func_001DDBF0(char *pch)
{
    float g;
    void *pv;
    if (g_joy.x100C == 1 && g_joy.x1010 == 0) {
        func_0021ED58(pch, func_0013E368(&D_003DD490, 9));
        return;
    }
    g = 0.0f;
    pv = D_002E65E0.xFD54;
    if (pv) {
        CRef ref = func_002581C0(D_003DD490.x3B1C, pv);
        g = ref.m_g;
    }
    {
        int ids = g != 0.0f ? 6 : 5;
        func_0021ED58(pch, func_0013E368(&D_003DD490, ids));
    }
    func_0021EDA0(pch, D_002A7A70);
    func_0021EDA0(pch, func_0013E368(&D_003DD490, 8));
    if (func_001A2C98() >= 2) {
        func_0021EDA0(pch, D_002A7A70);
        func_0021EDA0(pch, func_0013E368(&D_003DD490, 0x56));
    }
}
