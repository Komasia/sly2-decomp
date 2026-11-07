struct C { char pad[0xE4]; int xe4; };
struct S { int a, b, c; struct C *pc; int d, e; int x18; };
float SMinCrv__FP3CRV(struct C *);
float SMaxCrv__FP3CRV(struct C *);
void func_0019E110(struct S *p, float *ag) {
    if (p->pc->xe4) {
        ag[0] = -3.40282346638528859812e+38f;
        ag[1] = 3.40282346638528859812e+38f;
    } else if (p->x18) {
        ag[0] = SMinCrv__FP3CRV(p->pc) + 35.0f;
        ag[1] = SMaxCrv__FP3CRV(p->pc) - 100.0f;
    } else {
        ag[0] = SMinCrv__FP3CRV(p->pc) + 100.0f;
        ag[1] = SMaxCrv__FP3CRV(p->pc) - 35.0f;
    }
}
