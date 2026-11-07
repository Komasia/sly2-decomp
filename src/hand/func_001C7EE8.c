typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pf)(); };
struct LO { char pad[0xC]; struct VTE *vt; char p1[0x100 - 0x10]; int x100; };
struct S {
    char pad[0xC]; struct VTE *vt;
    char p0[0x150 - 0x10]; int x150;
    char p1[0x210 - 0x154]; struct LO *x210;
};
struct M { int n; struct S *p; int pad[14]; };
extern char g_sw[];
void *PsndNewPlain__Fi(int n);
void SetSource__4CSndPv(void *p, int n);
qword PosOfLo__FP2LO(struct S *p);
void *func_00156B98(void *pg, int n, qword q, struct S *p);
struct LO *PproxyOfInstance__FP2LO(struct S *p);
int FIsBasicDerivedFrom__FP5BASIC3CID(struct LO *p, int n);
void func_001C7C30(int n, int f);
void func_001618B0(void *pg);
void SetPickupStateBase__FP2LOi(struct S *p, int n);
static inline int FTest(struct S *p) { struct LO *q = PproxyOfInstance__FP2LO(p); return q && FIsBasicDerivedFrom__FP5BASIC3CID(q, 7); }
// name: SafeHouse port (SetClueState)
void SetClueState__FP2LOi(struct S *p, int n)
{
    struct LO *q;
    char *pg;
    qword qv;
    if (n == p->x150) return;
    if (n == 1) {
        struct LO *plo = p->x210;
        if (plo) {
            struct M m;
            m.n = n;
            m.p = p;
            ((void (*)(void *, struct M *))plo->vt[51].pf)((char *)plo + plo->vt[51].d, &m);
        } else {
            SetSource__4CSndPv(PsndNewPlain__Fi(0x29), 0);
        }
        pg = g_sw;
        n = 2;
        qv = PosOfLo__FP2LO(p);
        func_00156B98(pg, 0, qv, p);
        ((void (*)(void *, int, int, int, int, int))p->vt[3].pf)((char *)p + p->vt[3].d, 5, 0, 0, 0, 0);
        q = PproxyOfInstance__FP2LO(p);
        if (q && FIsBasicDerivedFrom__FP5BASIC3CID(q, 7)) {
            struct LO *plo = PproxyOfInstance__FP2LO(p);
            func_001C7C30(plo->x100, 1);
            ((void (*)(void *))plo->vt[9].pf)((char *)plo + plo->vt[9].d);
            func_001618B0(pg);
        }
    }
    SetPickupStateBase__FP2LOi(p, n);
}
