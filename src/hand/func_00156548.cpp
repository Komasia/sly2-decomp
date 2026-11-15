typedef int qword __attribute__((mode(TI)));
#include "vtbl.h"
struct VT { VTENT a[3]; VTENT a3; };
struct P { int n0; char pad[0x64 - 4]; int n64; };
struct S { int n0; int n4; int n8; VT *pvt; int n10; P *p14; int pad18[2]; qword q20; qword q30; int n40; int pad44; int n48; float f4C; int n50; int n54; int pad58[2]; };
struct SW { char pad[0x3D68]; int c; char pad2[0x3FFC - 0x3D6C]; char dl[0xC]; char pool[0x10]; };
extern SW g_sw;
extern VT D_002CE2B8;
#include "clock.h"
extern "C" {
S *func_0011CCC0(void *);
void *s1_memset(void *, int, int) asm("memset");
void AppendDlEntry(void *, S *) asm("AppendDlEntry__FP2DLPv");
void func_00256EE0(S *, int);
}
struct Lock {
    S *p;
    Lock(S *pp) { p = pp; ((void (*)(void *))p->pvt->a[1].pfn)(VT_THIS(p, &p->pvt->a[1])); }
    ~Lock() { ((void (*)(void *))p->pvt->a[2].pfn)(VT_THIS(p, &p->pvt->a[2])); }
};
// name: SafeHouse port (PnoiseNew)
extern "C" void PnoiseNew__FP9NOISETMPLG9VU_VECTORiP6VECTOR(P *p, qword q, int b, S **pps)
{
    S *ps = func_0011CCC0(g_sw.pool);
    s1_memset(ps, 0, 0x60);
    ps->n0 = 0;
    ps->n4 = 0;
    ps->p14 = p;
    ps->q20 = q;
    ps->q30 = q;
    ps->pvt = &D_002CE2B8;
    ps->n40 = b;
    ps->n48 = ++g_sw.c;
    ps->f4C = g_clock.t;
    ps->n54 = p->n64;
    AppendDlEntry(g_sw.dl, ps);
    ((void (*)(void *))ps->pvt->a[1].pfn)(VT_THIS(ps, &ps->pvt->a[1]));
    Lock l(ps);
    func_00256EE0(ps, p->n0);
    if (pps) *pps = ps;
    ((void (*)(void *, int, int, int, int, int))ps->pvt->a3.pfn)(VT_THIS(ps, &ps->pvt->a3), 2, 0, 0, 0, 0);
}
