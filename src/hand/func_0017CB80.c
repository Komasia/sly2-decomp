typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
extern float D_002BE74C;
struct L { int pad[2]; void *p8; };
struct T { char pad[0x40]; struct L *p40; };
struct A { char pad[0xF84]; void *pF84; float fF88; int nF8C; char pad2[0xFD0 - 0xF90]; char aFD0[4]; };
struct S { char pad[0x10]; struct A *p10; int pad2; struct T *p18; char pad3[0x14]; int n30; int pad4; float f38; float f3C; };
union V { qword q; float f[4]; };
void Update__5AIJOB(struct S *p);
qword PosOfLo__FP2LO(void *p);
float SWrapCrv__FP3CRVf(void *p, float f);
void NearestCrvS__FP3CRVG9VU_VECTORPvP6VECTORT3PfT5f(void *p, float f, qword v, int a, int b, union V *pv, int c, float *pt);
int func_0017CE30(struct S *p);
void SetRailState__7JOBRAILi(struct S *p, int n);
float func_002458F0(float y, float x);
void SetMoveHeading__FP7MOVEREF(void *p, float f);
void func_00131A00(void *p, float f);
// name: SafeHouse port (JOBRAIL::Update)
void Update__7JOBRAIL(struct S *p) {
    int s;
    Update__5AIJOB(p);
    do {
        s = p->n30;
        if (s == 0) {
            struct A *a = p->p10;
            void *q = a->pF84;
            float t = a->fF88;
            qword pos;
            union V v;
            a->nF8C = t < p->f3C;
            pos = PosOfLo__FP2LO(p->p10);
            NearestCrvS__FP3CRVG9VU_VECTORPvP6VECTORT3PfT5f(q, SWrapCrv__FP3CRVf(q, p->p10->nF8C ? t + D_002BE74C : t - D_002BE74C), pos, 0, 0, &v, 0, &t);
            p->p10->fF88 = t;
            if (func_0017CE30(p)) {
                SetRailState__7JOBRAILi(p, 1);
            } else {
                if (p->p10->nF8C == 0) {
                    qword w = v.q;
                    U u;
                    __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(-1.0f));
                    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(v.q) : "j"(w), "j"(u.q));
                }
                SetMoveHeading__FP7MOVEREF(p->p10->aFD0, func_002458F0(v.f[1], v.f[0]));
                func_00131A00(p->p18->p40->p8, p->f38);
            }
        }
    } while (p->n30 != s);
}
