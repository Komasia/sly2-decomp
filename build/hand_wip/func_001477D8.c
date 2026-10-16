// DRAFT (Claude agent): HUD 2-matrix GIF sprite draw (state loop 0..2 over x164/x168/x16C; logic complete, regalloc/frame not yet: extra f21-f23, p in s1 vs s3).
typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
struct M4 { qword r[4]; };
struct GIFS { int a[16]; };
struct TEX { ulong ul0; ulong pad; ulong ul10; };
struct X { char pad[0x24]; void *x24; char pad2[0x30 - 0x28]; int x30; };
struct P { char pad[0x60]; void *p60; char pad2[0x150 - 0x64]; int x150; int pad154; char *ap158[2]; int pad160; int x164; int x168; int x16C; };
extern struct X *D_002DEA4C;
extern void *D_002DEA34;
extern struct GIFS D_002DEA00;
extern struct TEX D_002DECD0;
extern char D_002DF4B0[];
extern float D_002BD398[];
extern float D_002BD39C[];
extern qword D_002BD3B0[4];
extern float D_002BD3F0[8];
extern struct M4 D_002BD410;
void func_001475C0(struct P *p);
void func_00147410(struct P *p, int n);
void func_001576F0(struct GIFS *pgifs);
void func_00157500(struct GIFS *pgifs, int n, void *pv);
void func_001574B8(struct GIFS *pgifs);
void func_00166BD8(struct GIFS *pgifs, int a, int b, int c);
void func_00166E90(struct GIFS *pgifs, int reg, ulong val);
void func_0022FF40(struct M4 *pm, int n, void *p, void *q);
qword func_0011C1A8(struct M4 *pm, qword v);
void func_0011D9D8(void *pv);
void func_00166D38(struct GIFS *pgifs, float s, float t, float q);
void func_00166C70(struct GIFS *pgifs, int rgba);
void func_00166DA0(struct GIFS *pgifs, int x, int y, int z);

void func_001477D8(struct P *p)
{
    struct M4 am[2];
    union { qword q; float f[4]; struct M4 m; } u;
    float rw;
    int i, state, stateNext;
    switch (p->x150) {
    case 1:
        func_001475C0(p);
        func_00147410(p, 2);
        break;
    case 2:
    case 3:
        break;
    default:
        return;
    }
    D_002DEA4C->x30 &= ~1;
    if (!D_002DEA4C->x24)
        D_002DEA4C->x24 = D_002DEA34;
    func_001576F0(&D_002DEA00);
    func_00157500(&D_002DEA00, 0x25, D_002DF4B0);
    func_001574B8(&D_002DEA00);
    func_00166BD8(&D_002DEA00, 0, 1, 0xE);
    func_00166E90(&D_002DEA00, 0x47, 0x31001);
    func_00166E90(&D_002DEA00, 6, ((D_002DECD0.ul10 & 0x1FF) << 5) | (((D_002DECD0.ul0 >> 16) & 0x3F) << 14) | 0x6A800000000UL);
    func_00166E90(&D_002DEA00, 0x14, 0x61);
    func_00166E90(&D_002DEA00, 0x3F, 0);
    func_00166E90(&D_002DEA00, 8, 0x380000800000AUL);
    for (i = 0; i < 2; i++) {
        func_0022FF40(&u.m, 0, p->p60, p->ap158[i] + 0x40);
        am[i] = u.m;
    }
    state = 0;
    do {
        switch (state) {
        case 0:
            stateNext = 1;
            if (!p->x164 || !p->x16C)
                goto next;
            break;
        case 1:
            stateNext = 2;
            if (!p->x168)
                goto next;
            break;
        case 2:
            stateNext = 3;
            if (!p->x164 || p->x16C)
                goto next;
            break;
        }
        func_00166BD8(&D_002DEA00, 0x14, 3, 0x512);
        {
            int t = state & 1;
            int j;
            stateNext = state + 1;
            for (j = 0; j < 4; j++) {
                u.q = func_0011C1A8(&D_002BD410, func_0011C1A8(&am[t], D_002BD3B0[j]));
                func_0011D9D8(&u);
                rw = 1.0f / u.f[3];
                {
                    qword s;
                    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(rw));
                    __asm__("vmulx.xyzw %0, %0, %1x" : "+j"(u.q) : "j"(s));
                }
                func_0011D9D8(&rw);
                func_0011D9D8(&u);
                u.f[0] = (u.f[0] + 0.5f) * 512.0f + 0.5f;
                u.f[1] = (u.f[1] + 0.5f) * 224.0f + 0.5f;
                func_0011D9D8(&u);
                func_00166D38(&D_002DEA00, rw * (D_002BD3F0[j * 2] + D_002BD398[t * 2]),
                              rw * (D_002BD3F0[j * 2 + 1] + D_002BD39C[t * 2]), rw);
                func_00166C70(&D_002DEA00, 0x80808080);
                func_00166DA0(&D_002DEA00, ((int)u.f[0] + 0x700) << 4, ((int)u.f[1] + 0x790) << 4, 0);
            }
        }
    next:
        state = stateNext;
    } while (state < 3);
}
