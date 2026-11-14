#include "clock.h"
struct P { char pad[0x90]; int state; float tState; };
void EnterPad__FP2LO(struct P *p);
void LeavePad__FP2LO(struct P *p);
// name: SafeHouse port (SetTriggerState)
void SetTriggerState__FP2LOi(struct P *p, int state)
{
    int f1, f2; int old = p->state; if (old == state) return; f1 = old == 0 && state == 1; f2 = old != -1 && state == 0;
    p->state = state;
    p->tState = g_clock.t;
    if (f1) EnterPad__FP2LO(p);
    if (f2) LeavePad__FP2LO(p);
}
