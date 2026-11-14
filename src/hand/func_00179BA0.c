#include "clock.h"
struct S { char pad[0x10]; void *p10; int pad2; void *p18; char pad3[0x14]; float f30; float f34; int n38; char pad4[4]; int n40; };
void Update__5AIJOB(struct S *p);
int func_00209098(void *p);
int FJobDone(struct S *p) asm("FJobDone__FP5AIJOB");
void SetWaitState__7JOBWAITi(struct S *p, int n);
int func_00171458(void *p);
// name: SafeHouse port (JOBWAIT::Update)
void Update__7JOBWAIT(struct S *p) {
    int f, s;
    Update__5AIJOB(p);
    f = func_00209098(p->p10);
    while (!FJobDone(p)) {
        s = p->n38;
        switch (s) {
        case 1:
            if (f) SetWaitState__7JOBWAITi(p, 3);
            else if (g_clock.t > p->f34) SetWaitState__7JOBWAITi(p, 0);
            break;
        case 2:
            if (f) SetWaitState__7JOBWAITi(p, 3);
            break;
        case 0:
            if (f) SetWaitState__7JOBWAITi(p, 3);
            else if (g_clock.t > p->f30) SetWaitState__7JOBWAITi(p, 1);
            else if (func_00171458(p->p18)) { p->n40 = 0; SetWaitState__7JOBWAITi(p, 2); }
            break;
        case 3:
            if (!f) {
                if (p->n40) SetWaitState__7JOBWAITi(p, 1);
                else SetWaitState__7JOBWAITi(p, 2);
            }
            break;
        }
        if (p->n38 != s) continue;
        break;
    }
}
