/* wip: 41 diffs - register allocation only (0x10 const s2 vs s1, i/e share s1 with i+1 in s2 in target) and 1C3C store scheduling. Logic complete. */
struct MSG { int cb; int nKind; };
typedef struct { int a[16]; } M64;
struct E { int c; short *a; };
extern int D_003E1C38;
extern int D_003E1C3C;
extern M64 *D_003E1C40;
extern int *D_003E1C44;
extern int *D_003E1C48;
extern struct E *D_003E1C4C;
extern M64 *D_003E1C50;
int func_00117C80(void *ps);
int func_00117BD0(void *ps);
short func_00117C20(void *ps);
void func_00118458(void *ps, M64 *pm);
void *func_001AE1D0(struct MSG *pmsg);
void *func_001AE2A0(struct MSG *pmsg);

void func_0020F318(void *p, void *ps)
{
    struct MSG msg;
    int i, j;
    D_003E1C38 = func_00117C80(ps);
    D_003E1C3C = func_00117C80(ps);
    msg.cb = D_003E1C38 << 6;
    msg.nKind = 0x10;
    D_003E1C40 = func_001AE1D0(&msg);
    msg.cb = D_003E1C38 << 2;
    msg.nKind = 0x10;
    D_003E1C44 = func_001AE1D0(&msg);
    msg.cb = D_003E1C38 << 2;
    msg.nKind = 0x10;
    D_003E1C48 = func_001AE1D0(&msg);
    msg.cb = D_003E1C38 << 3;
    msg.nKind = 0x10;
    D_003E1C4C = func_001AE1D0(&msg);
    msg.cb = 0x240;
    msg.nKind = 0x10;
    D_003E1C50 = func_001AE2A0(&msg);
    for (i = 0; i < D_003E1C38; i++) {
        struct E *e;
        func_00118458(ps, &D_003E1C40[i]);
        D_003E1C44[i] = func_00117BD0(ps);
        D_003E1C48[i] = func_00117BD0(ps);
        if (func_00117BD0(ps))
            D_003E1C50[D_003E1C44[i]] = D_003E1C40[i];
        e = &D_003E1C4C[i];
        e->c = func_00117BD0(ps);
        msg.cb = e->c * 2;
        msg.nKind = 0x10;
        e->a = func_001AE1D0(&msg);
        for (j = 0; j < e->c; j++)
            e->a[j] = func_00117C20(ps);
    }
}
