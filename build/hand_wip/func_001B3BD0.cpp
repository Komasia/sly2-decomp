struct CTX { int a[4]; CTX(); ~CTX(); };
struct AREQ { int cb; int align; AREQ(int c, int a) { cb = c; align = a; } };
struct K;
struct X {
    int x0; int x4; int x8; char pad[0x110 - 0xC];
    X() { x8 = 2; Init(); }
    void Init() __asm__("func_00258248");
    bool FSet(K *k);
};
struct K { int x0; int x4; int x8; char pad[0x34 - 0xC]; int x34; int x38; int x3C; };
struct STRM { char pad[0x30]; STRM(int cb, void *pv) __asm__("func_00132570"); ~STRM(); };
struct G { char pad[0xFD50]; int xFD50; };
struct P { char pad[0x108]; int x108; int pad10C; void *x110; int pad114; char x118[4]; };
extern "C" {
extern K D_002A3968;
extern K D_002A39A8;
extern int D_002F68F8;
extern int D_002C0268;
extern int D_002BD4C0;
extern G D_002E65E0;
extern char D_002DDED0[];
extern char D_002DFC00[];
void *func_001AE378(const AREQ &r);
void func_00258248(X *px);
int func_00132600(STRM *ps, X *px);
void func_001B3EC0(P *p, STRM *ps);
int func_0024B610(void *p);
void func_0014D0B8(void *p, int k);
void func_001871C0(void *p);
void func_001AB1A0(void);
int func_00187D80(void *p, int k);
void func_0014BA38(void);
void func_001B4058(P *p);
void func_001B4140(P *p);
void func_00132688(STRM *ps);
}

inline bool X::FSet(K *k)
{
    if (!k) return 0;
    x0 = (k->x0 ^ k->x34) + 0xCA0;
    x4 = k->x4 ^ k->x3C;
    x8 = 2;
    return x4;
}

static inline int FMatch(K *a, K *b)
{
    if (a == b) return 1;
    if (!a || !b) return 0;
    return ((a->x8 ^ a->x38) ^ (b->x8 ^ b->x38)) == 0;
}

static inline int GetKey(X *px, K *k)
{
    if (!k) return 0;
    px->x0 = (k->x0 ^ k->x34) + 0xCA0;
    px->x4 = k->x4 ^ k->x3C;
    px->x8 = 2;
    return px->x4;
}

extern "C" void func_001B3BD0(P *p, K *k)
{
    CTX ctx;
    p->x110 = func_001AE378(AREQ(0x41FC00, 0x40));
    STRM strm(0x80000, p->x110);
    X x;
    bool ok = x.FSet(k);
    if (ok && func_00132600(&strm, &x)) {
        func_001B3EC0(p, &strm);
        while (!func_0024B610(p->x118)) {
            int f;
            func_0014D0B8(D_002DDED0, 1);
            func_001871C0(D_002DFC00);
            if (!D_002E65E0.xFD50) func_001AB1A0();
            f = 0;
            if (FMatch(k, &D_002A3968) || FMatch(k, &D_002A39A8)) f = D_002F68F8 != 0;
            if (D_002C0268) f = 1;
            bool fQuit = f && func_00187D80(D_002DFC00, 0x91F);
            if (fQuit) {
                p->x108 = 0;
                break;
            }
            if (x.x8 == 2) func_0014BA38();
            if (D_002BD4C0 == 3) func_001B4058(p);
        }
        if (FMatch(k, &D_002A39A8)) D_002F68F8 = 1;
        func_001B4140(p);
        func_00132688(&strm);
    }
    p->x110 = 0;
}
