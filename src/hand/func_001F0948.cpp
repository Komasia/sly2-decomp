#include "vtbl.h"
struct VT { VTENT a[3]; };
struct P { char pad[0xC]; VT *pvt; char pad2[0x24 - 0x10]; void *p24; char pad3[0x3C - 0x28]; int n3C; };
extern "C" int FSmaRetracted(P *) asm("FSmaRetracted__FP3SMA");
extern "C" int IsmsFindSmRequired__FP2SM3OID(void *, int);
extern "C" void FinishSmaTransition(P *) asm("FinishSmaTransition__FP3SMA");
extern "C" void ChooseSmaTransition(P *, int) asm("ChooseSmaTransition__FP3SMAi");
struct Lock {
    P *p;
    Lock(P *pp) { p = pp; ((void (*)(void *))p->pvt->a[1].pfn)(VT_THIS(p, &p->pvt->a[1])); }
    ~Lock() { ((void (*)(void *))p->pvt->a[2].pfn)(VT_THIS(p, &p->pvt->a[2])); }
};
// name: SafeHouse port (SnapSmaGoal)
extern "C" void SnapSmaGoal__FP3SMA3OID(P *p, int n)
{
    if (!FSmaRetracted(p)) {
        Lock l(p);
        p->n3C = IsmsFindSmRequired__FP2SM3OID(p->p24, n);
        FinishSmaTransition(p);
        ChooseSmaTransition(p, 1);
    }
}
