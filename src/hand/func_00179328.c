typedef int qword __attribute__((mode(TI)));
#include "clock.h"
struct G;
extern struct G g_sw;
extern qword D_002A2DD0;
extern float D_002A5584;
extern void *D_002F7900;
extern char g_joy[];
struct E4 { char pad[0x1C]; float f1C; };
struct E { int n0; struct E4 *p4; void *p8; };
struct A { char pad[0x1A8]; float f1A8; char pad2[0x334 - 0x1AC]; int n334; char pad3[0x35C - 0x338]; char a35C[4]; char pad4[0xF04 - 0x360]; int nF04; char pad5[0xFD0 - 0xF08]; char aFD0[4]; };
struct S { char pad[0x10]; struct A *p10; char pad2[0x1C]; int n30; char pad3[0xC]; struct E *p40; char pad4[0xC]; int n50; char pad5[8]; int n5C; char pad6[0x20]; union { qword v; float f[4]; } v80; char pad7[0x20]; float fB0; float fB4; };
void Enter__7JOBMOVE(struct S *p);
float atan2f(float y, float x);
float *MatJtLo__FP2LO(struct A *a);
void SetMoveHeading__FP7MOVEREF(void *p, float f);
float RadNormalize__Ff(float f);
qword SetVectorCylind__Ffff(float a, float b, float c);
qword PosOfLo__FP2LO(void *p);
void SetK2Target__FP6K2PLAYG9VU_VECTOR(void *p, qword v);
void SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(struct A *a, int b, int c, qword v);
void LockJob__FP5AIJOB(struct S *p);
void func_00156C80(struct G *g, int n, qword v, struct A *a, void *q);
void *PloPlayerPo__FP2SW(struct G *g);
int FLoInParentChain__FP2LOT0(int n, void *o);
void TriggerJoyRumbleRumk__FP3JOY4RUMKf(void *p, int n, float f);
// name: SafeHouse port (JOBHIT::Enter)
void Enter__6JOBHIT(struct S *p) {
    int f;
    float a;
    struct E *e;
    Enter__7JOBMOVE(p);
    {
        qword d, one, l;
        float g;
        __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(p->v80.v));
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
        __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
        f = 0;
        if (g > 1.0e-4f) f = p->n5C != 0x40000;
    }
    if (f) {
        a = atan2f(-p->v80.f[1], -p->v80.f[0]);
    } else {
        float *m = MatJtLo__FP2LO(p->p10);
        a = atan2f(m[1], MatJtLo__FP2LO(p->p10)[0]);
    }
    SetMoveHeading__FP7MOVEREF(p->p10->aFD0, a);
    e = p->p40;
    if (e && e->n0 == 2) {
        qword r = SetVectorCylind__Ffff(RadNormalize__Ff(p->p10->f1A8 + 3.14159274101257324219e+00f), p->p40->p4->f1C, 0.0f);
        qword pos = PosOfLo__FP2LO(p->p10);
        qword s;
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(s) : "j"(pos), "j"(r));
        SetK2Target__FP6K2PLAYG9VU_VECTOR(p->p40->p8, s);
    }
    SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(p->p10, 0, 0, D_002A2DD0);
    if (p->n30 == 0) LockJob__FP5AIJOB(p);
    func_00156C80(&g_sw, 1, PosOfLo__FP2LO(p->p10), p->p10, p->p10->a35C);
    p->fB0 = p->fB4 = D_002A5584;
    p->p10->nF04 = 0;
    if (p->p10->n334) {
        void *o = PloPlayerPo__FP2SW(&g_sw);
        if (o && FLoInParentChain__FP2LOT0(p->n50, o) && (o == D_002F7900 || (p->n5C & 0x40000))) {
            TriggerJoyRumbleRumk__FP3JOY4RUMKf(g_joy, 3, 1.50000005960464477539e-01f);
            p->fB0 = g_clock.t + 5.00000044703483581543e-02f;
        }
        p->fB4 = g_clock.t + 1.33333340287208557129e-01f;
    }
}
