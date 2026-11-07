
struct S { char pad[0xE8]; int c; };
float GMaxCrv__FP3CRV(struct S *p);
float GMinCrv__FP3CRV(struct S *p);
// name: SafeHouse port (DgStepCrv)
float DgStepCrv__FP3CRV(struct S *p)
{
    float a = GMaxCrv__FP3CRV(p);
    return (a - GMinCrv__FP3CRV(p)) / (p->c * 10.0f);
}
