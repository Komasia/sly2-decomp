typedef int qword __attribute__((mode(TI)));
#include "clock.h"
extern float D_002BE760, D_002BE764, D_002BE768;
struct VTE { short d; short pad; void *pfn; };
struct X { qword a; qword v; };
struct T { char pad[0x40]; struct X x40; };
struct A { char pad[0xC]; struct VTE *vt; };
struct S { char pad[0x10]; struct A *p10; int pad2; struct T *p18; char pad3[0x14]; int n30; int pad4; void *p38; float f3C; float f40; };
void Update__5AIJOB(struct S *p);
int FJobDone(struct S *p) asm("FJobDone__FP5AIJOB");
int func_00174FB8(void *p);
int func_00209098(void *p);
void SetState__5JOBBDi(struct S *p, int n);
int func_00208B38(struct A *a, void *o);
float func_00208BB0(struct A *a);
qword PosOfLo__FP2LO(void *p);
qword PosGoal__FP4GOALG9VU_VECTOR(struct X *s, qword v);
void ChooseAway__5JOBBD(struct S *p);
static __inline__ float Dist(qword a, qword b) {
    qword d;
    float f;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(d));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    return f;
}
// name: SafeHouse port (JOBBD::Update)
void Update__5JOBBD(struct S *p) {
    int s;
    Update__5AIJOB(p);
    while (s = p->n30, !FJobDone(p)) {
        switch (p->n30) {
        case 0:
            if (func_00174FB8(p->p18)) SetState__5JOBBDi(p, 1);
            break;
        case 1:
            if (func_00209098(p->p10)) {
                SetState__5JOBBDi(p, 2);
            } else {
                { float dt = g_clock.dt; p->f40 -= dt; }
                if (p->f40 <= 0.0f) {
                    void *o;
                    { struct A *a = p->p10; struct VTE *e = &a->vt[0x58]; o = ((void *(*)(void *))e->pfn)((char *)a + e->d); }
                    if (o == p->p38 && func_00208B38(p->p10, o)) {
                        p->f40 = func_00208BB0(p->p10);
                    } else {
                        SetState__5JOBBDi(p, -1);
                    }
                }
            }
            break;
        case 2:
            if (!func_00209098(p->p10)) SetState__5JOBBDi(p, 1);
            break;
        }
        if (p->n30 != s) continue;
        break;
    }
    if (p->n30 == 1) {
        struct T *t = p->p18;
        if (g_clock.t - p->f3C > D_002BE760) {
        struct X *x = &t->x40;
        qword pos = PosOfLo__FP2LO(p->p10);
        int f = 0;
        qword q = PosGoal__FP4GOALG9VU_VECTOR(x, pos);
        if (Dist(PosOfLo__FP2LO(p->p10), q) < D_002BE764) {
            f = 1;
        } else if (Dist(PosOfLo__FP2LO(p->p10), PosOfLo__FP2LO(p->p38)) < D_002BE768) {
            f = 1;
        }
        if (f) ChooseAway__5JOBBD(p);
        }
    }
}
