typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct O { char pad[0xE4]; int xe4; };
struct Q { int x0; int x4; float x8; int xc; U x10; qword x20; };
struct HIT { qword a; U b; qword c[4]; };
struct P { char pad[0x4D4]; struct O *x4d4; int pad2[2]; float x4e0; int x4e4; };
extern qword D_002A2DD0;
void SetCtrlSourceOffset__FP10CTRLSOURCEG9VU_VECTOR(void *r, qword q);
float SMinCrv__FP3CRV(struct O *o);
float SMaxCrv__FP3CRV(struct O *o);
float GModPositive__Fff(float g, float hi);
void EvalCrvS(struct O *o, float g, U *pv, int n) asm("EvalCrvS__FP3CRVfP6VECTORT2");
qword ConvertPos__FP2LOT0G9VU_VECTOR(int n, struct P *p, qword q);
int ClipSegmentSphere__FG9VU_VECTORfN20iP3LSG(qword a, float g, qword b, qword c, int n, struct HIT *pv);
static __inline__ float GClamp(float g, float lo, float hi)
{
    if (g < lo)
        return lo;
    if (g > hi)
        return hi;
    return g;
}
void func_00193C98(struct P *p, struct Q *q, void *r)
{
    struct O *o;
    float g, lo, hi, t;
    U v;
    struct HIT hit;
    qword d;
    if (!q->x4) {
        SetCtrlSourceOffset__FP10CTRLSOURCEG9VU_VECTOR(r, D_002A2DD0);
        return;
    }
    o = p->x4d4;
    g = q->x10.f;
    if (p->x4e4)
        g = -g;
    lo = SMinCrv__FP3CRV(o);
    hi = SMaxCrv__FP3CRV(o);
    if (o->xe4)
        t = GModPositive__Fff(p->x4e0 + g, hi);
    else
        t = GClamp(p->x4e0 + g, lo, hi);
    EvalCrvS(o, t, &v, 0);
    v.q = ConvertPos__FP2LOT0G9VU_VECTOR(0, p, v.q);
    if (ClipSegmentSphere__FG9VU_VECTORfN20iP3LSG(q->x20, q->x8, q->x10.q, v.q, 1, &hit) > 0) {
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(hit.b.q), "j"(q->x10.q));
        SetCtrlSourceOffset__FP10CTRLSOURCEG9VU_VECTOR(r, d);
    }
}
