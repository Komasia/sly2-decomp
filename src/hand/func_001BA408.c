typedef int qword __attribute__((mode(TI)));
#include "clock.h"
extern int D_002E1E40;
extern qword D_002A2DD0;
struct VE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VE *vt; char pad1[0x38 - 0x10]; int x38; };
struct S { char pad[0x1018]; int x1018; float f101C; int x1020; struct O *x1024; int x1028; int x102C; int x1030; int x1034; };
#define VCALL0(o, n) ((void (*)())(o)->vt[n].pfn)((char *)(o) + (o)->vt[n].d)
void RetractAsega__FP5ASEGA(struct O *o);
void DeleteCtrl__FPP4CTRL(int *p);
int FGuardState(struct S *p, int n) asm("FGuardState__FP5GUARDi");
struct O *func_00205458(struct S *p, int n);
void SetStepPhysScale__FP3ALOf(struct S *p, float f);
void ApplyAseg__FP4ASEGiiffPP5ASEGA(int a, struct S *p, int n, struct O **ppo, float f1, float f2);
int PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(struct S *p, int a, int b, int c, int d, qword q);
// name: SafeHouse port (SetStrikeState)
void SetStrikeState__FP5GUARDi(struct S *p, int st)
{
    if (st == p->x1018) return;
    if (p->x1018 == 1) {
        RetractAsega__FP5ASEGA(p->x1024);
        VCALL0(p->x1024, 2);
        p->x1024 = 0;
        DeleteCtrl__FPP4CTRL(&p->x102C);
        p->x102C = 0;
        p->x1028 = 0;
        if (FGuardState(p, 2)) func_00205458(p, 0x9E)->x38 = D_002E1E40;
        SetStepPhysScale__FP3ALOf(p, 1.0f);
    }
    p->x1018 = st;
    p->f101C = g_clock.t;
    if (st != 1) return;
    ApplyAseg__FP4ASEGiiffPP5ASEGA(p->x1020, p, 1, &p->x1024, 0.0f, 1.0f);
    VCALL0(p->x1024, 1);
    p->x102C = PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(p, p->x1034, 5, 8, 3, D_002A2DD0);
    if (FGuardState(p, 2)) {
        func_00205458(p, 0x9E)->x38 = p->x1028;
        SetStepPhysScale__FP3ALOf(p, 4.0f);
    }
}
