#include "vtbl.h"
struct VT { VTENT a[3]; VTENT a3; };
struct P { int n0; char pad[0xC - 4]; VT *pvt; char pad2[0x68 - 0x10]; char dl68[0xC]; };
struct S { int n0; int n4; int n8; VT *pvt; char pad[0x24 - 0x10]; P *p24; int n28; int n2C; int pad30; int n34; int n38; int n3C; int pad40; float f44; int n48; int pad4C; };
struct SW { char pad[0x3DDC]; char dl[0xC]; char pool[0x10]; };
extern SW g_sw;
extern VT D_002D9768;
extern "C" {
S *func_0011CCC0(void *);
void *s1_memset(void *, int, int) asm("memset");
void AppendDlEntry(void *, S *) asm("AppendDlEntry__FP2DLPv");
void func_00256EE0(S *, int);
int FSmaRetracted(S *) asm("FSmaRetracted__FP3SMA");
int IsmsFindSmRequired__FP2SM3OID(P *, int);
void NotifySmaState(S *, int, int) asm("NotifySmaState__FP3SMAii");
void ChooseSmaTransition(S *, int) asm("ChooseSmaTransition__FP3SMAi");
}
struct Lock {
    P *p;
    Lock(P *pp) { p = pp; ((void (*)(void *))p->pvt->a[1].pfn)(VT_THIS(p, &p->pvt->a[1])); }
    ~Lock() { ((void (*)(void *))p->pvt->a[2].pfn)(VT_THIS(p, &p->pvt->a[2])); }
};
// name: SafeHouse port (PsmaApplySm)
extern "C" void PsmaApplySm__FP2SM3OIDiUiiPv(P *p, int a, int b, int c, int d, S **pps)
{
    S *ps = func_0011CCC0(g_sw.pool);
    *pps = ps;
    s1_memset(ps, 0, 0x50);
    ps->pvt = &D_002D9768;
    ps->n28 = a;
    ps->n2C = c;
    ps->n48 = d;
    ps->n0 = 0;
    ps->n4 = 0;
    ps->p24 = p;
    ps->n38 = -1;
    ps->f44 = 1.0f;
    AppendDlEntry(g_sw.dl, ps);
    AppendDlEntry(p->dl68, ps);
    ((void (*)(void *))ps->pvt->a[1].pfn)(VT_THIS(ps, &ps->pvt->a[1]));
    Lock l(p);
    func_00256EE0(ps, p->n0);
    ((void (*)(void *, int, int, int, int, int))ps->pvt->a3.pfn)(VT_THIS(ps, &ps->pvt->a3), 2, 0, 0, 0, 0);
    if (FSmaRetracted(ps)) return;
    if (b != -1) {
        int v = IsmsFindSmRequired__FP2SM3OID(p, b);
        ps->n34 = v;
        ps->n3C = v;
        NotifySmaState(ps, -1, v);
    }
    ChooseSmaTransition(ps, 0);
}
