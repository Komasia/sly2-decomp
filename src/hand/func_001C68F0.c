typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pf)(); };
struct MAT { qword a[3]; };
struct LO { char pad[0xC]; struct VTE *vt; };
struct S {
    char pad[0xC]; struct VTE *vt;
    char p0[0x150 - 0x10]; int x150;
    char p1[0x210 - 0x154]; struct LO *x210;
    char p2[0x230 - 0x214]; float x230; float x234; float x238; int x23C; int x240;
};
struct X {
    char pad[0x1C]; struct S *x1C; char p1[0x40 - 0x20]; struct MAT mat;
    char p2[0xEC - 0x70]; struct VTE *vt; void *xF0; struct S *xF4; int xF8;
};
struct M { int n; struct S *p; int pad[14]; };
extern char g_sw[];
extern char D_002C0E10[];
extern char g_game[];
float GRandInRange__Fff(float a, float b);
struct X *FLaunchHudRip__FP2LOP6VECTORP7MATRIX3(void *pg, int a, int b);
struct LO *PloPlayerPo__FP2SW(void *pg);
qword PosOfLo__FP2LO(struct S *p);
struct MAT *MatJtLo__FP2LO(struct S *p);
void func_001C6AB0(struct S *p, int n);
void *PsndNewPlain__Fi(int n);
void SetSource__4CSndPv(void *p, int n);
void ShowCoinCounter__FP2SW(void *pg);
void BroadcastTaskEvent__FP2SWiP2LO(void *p, int n, struct S *ps);
void SetPickupStateBase__FP2LOi(struct S *p, int n);
// name: SafeHouse port (SetCharmState)
void SetCharmState__FP2LOi(struct S *p, int n)
{
    if (p->x150 == n) return;
    switch (n) {
    case 0:
        p->x238 = GRandInRange__Fff(p->x230, p->x234);
        break;
    case 1: {
        struct LO *q = PloPlayerPo__FP2SW(g_sw);
        struct X *px;
        struct LO *plo;
        if (!((int (*)(void *))q->vt[80].pf)((char *)q + q->vt[80].d)) {
            n = p->x150;
            break;
        }
        px = FLaunchHudRip__FP2LOP6VECTORP7MATRIX3(g_sw, 9, 0);
        if (px) {
            struct VTE *e;
            px->xF4 = p;
            px->xF0 = D_002C0E10;
            px->xF8 = 0;
            e = &px->vt[1];
            ((void (*)(void *, qword, int, float))e->pf)((char *)px + e->d, PosOfLo__FP2LO(p), 0, 1.0f);
            px->x1C = p;
            px->mat = *MatJtLo__FP2LO(p);
        } else {
            func_001C6AB0(p, 0);
        }
        ((void (*)(void *, int, int))q->vt[81].pf)((char *)q + q->vt[81].d, p->x23C, p->x240);
        plo = p->x210;
        if (plo) {
            struct M m;
            m.n = 1;
            m.p = p;
            ((void (*)(void *, struct M *))plo->vt[51].pf)((char *)plo + plo->vt[51].d, &m);
        }
        n = 2;
        ((void (*)(void *, int, int, int, int, int))p->vt[3].pf)((char *)p + p->vt[3].d, 5, 0, 0, 0, 0);
        break;
    }
    }
    SetPickupStateBase__FP2LOi(p, n);
}
