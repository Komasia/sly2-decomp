typedef int qword __attribute__((mode(TI)));
typedef struct { short d; short pad; void *pfn; } VTE;
extern float D_002C3DA8;
struct O { char pad[0x50]; int k; };
struct S { char pad[0xC]; VTE *vt; };
int FGuardState(struct S *p, int n) asm("FGuardState__FP5GUARDi");
struct O *func_00205458(struct S *p, int n);
void SetState__5JOBB0i(struct O *o, int n);
void SetState__5JOBB1i(struct O *o, int n);
qword LimitVectorLength__FG9VU_VECTORf(qword v, float g);
// name: SafeHouse port (ReleaseGuardHeld)
void ReleaseGuardHeld__FP2LO(struct S *p)
{
    if (FGuardState(p, 0x12) || FGuardState(p, 0x13)) {
        SetState__5JOBB0i(func_00205458(p, 0xB0), 2);
    } else {
        struct O *o;
        if (!FGuardState(p, 0x17))
            return;
        o = func_00205458(p, 0xB1);
        if (o->k != 3 && o->k != 6)
            SetState__5JOBB1i(o, 2);
    }
    {
        qword v = ((qword (*)(void *))p->vt[33].pfn)((char *)p + p->vt[33].d);
        v = LimitVectorLength__FG9VU_VECTORf(v, D_002C3DA8);
        ((void (*)(void *, qword))p->vt[35].pfn)((char *)p + p->vt[35].d, v);
    }
}
