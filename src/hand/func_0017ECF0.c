typedef int qword __attribute__((mode(TI)));
extern float D_002BE7BC, D_002BE7C0, D_002BE7C4;
struct R { float f0; float f4; };
struct B { char pad[0xE4]; int nE4; char pad2[0x180 - 0xE8]; void *p180; };
struct X { qword a; qword v; };
struct S { char pad[0x10]; void *p10; int pad2; void *p18; char pad3[0x14]; struct B *p30; int n34; float f38; int pad4; qword v40; char pad5[8]; int n58; };
int FIsBasicDerivedFrom__FP5BASIC3CID(void *p, int n);
float SMinCrv__FP3CRV(struct B *b);
float SMaxCrv__FP3CRV(struct B *b);
float SWrapCrv__FP3CRVf(struct B *b, float f);
void func_001EA000(void *p);
struct R *func_001EA3B0(void *p, float f);
void func_001E6F10(struct B *b, float f, qword *pv, int n);
void func_002562A8(struct X *x);
void SetGoal__7JOBGOTOP4GOAL(void *p, struct X *x);
// name: SafeHouse port (JOBPATHSTEP::Step)
void Step__11JOBPATHSTEPi(struct S *p, int force) {
    float d;
    float t;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(p->p10, 0x3A)) d = D_002BE7BC; else d = D_002BE7C0;
    if (p->n34 == 0) d = -d;
    t = p->f38 + d;
    if (p->p30->nE4 == 0) {
        float lo = SMinCrv__FP3CRV(p->p30);
        float hi = SMaxCrv__FP3CRV(p->p30);
        if (t < lo) t = lo;
        else if (hi < t) t = hi;
    } else {
        t = SWrapCrv__FP3CRVf(p->p30, t);
    }
    if (p->n58 == 0) {
        struct R *r;
        func_001EA000(p->p30->p180);
        r = func_001EA3B0(p->p30->p180, t);
        if (r) t = SWrapCrv__FP3CRVf(p->p30, p->n34 != 0 ? r->f4 : r->f0);
    }
    if (force == 0 && __builtin_fabsf(p->f38 - t) < D_002BE7C4) return;
    {
        void *q;
        struct X x;
        p->f38 = t;
        func_001E6F10(p->p30, t, &p->v40, 0);
        q = p->p18;
        func_002562A8(&x);
        x.v = p->v40;
        SetGoal__7JOBGOTOP4GOAL(q, &x);
    }
}
