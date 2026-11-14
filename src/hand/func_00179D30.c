#include "clock.h"
struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { char pad[0xC]; struct VTE *vt; char pad2[0x2C]; int n3C; };
struct S { char pad[0x10]; char *p10; int pad2; void *p18; char pad3[0x14]; float g30; float g34; int n38; float g3C; void *p40; };
void EndChildJob__FPP5AIJOB(void *p);
struct O *func_00205438(void *p, int n);
void Save__9JOBSCRIPTP11SAVEDSCRIPT(void *p, void *q);
void SetTarget__9JOBSCRIPTP7CMDLISTiP11SAVEDSCRIPT(struct O *o, void *t, int a, void *u);
void func_00179EF8(struct S *p);
void func_00179E80(struct S *p);
// name: SafeHouse port (JOBWAIT::SetWaitState)
void SetWaitState__7JOBWAITi(struct S *p, int n) {
    if (n == p->n38) return;
    if (p->n38 == 0) Save__9JOBSCRIPTP11SAVEDSCRIPT(p->p18, p->p10 + 0x2DC);
    EndChildJob__FPP5AIJOB(&p->p18);
    p->n38 = n;
    p->g3C = g_clock.t;
    switch (n) {
    case 1: case 2:
        { struct O *o = func_00205438(p->p10, 0x9E); struct VTE *e = &o->vt[8]; e->pfn((char *)o + e->d); }
        func_00179EF8(p);
        p->g30 = 3.40282346638528859812e+38f;
        break;
    case 0:
        { struct O *o = func_00205438(p->p10, 0xA9); struct VTE *e; SetTarget__9JOBSCRIPTP7CMDLISTiP11SAVEDSCRIPT(o, p->p40, 0, p->p10 + 0x2DC); e = &o->vt[8]; e->pfn((char *)o + e->d); }
        func_00179E80(p);
        p->g34 = 3.40282346638528859812e+38f;
        break;
    case 3:
        { struct O *o = func_00205438(p->p10, 0x9E); struct VTE *e; o->n3C = 1; e = &o->vt[8]; e->pfn((char *)o + e->d); }
        break;
    }
}
