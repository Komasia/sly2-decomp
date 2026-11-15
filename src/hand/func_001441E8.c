/* only diff: hazard nop placement (target: no nop after mfc1 before beqz, nop after mtc1); assembler-level */
#include "clock.h"
int NActorPower__FP5ACTOR(void *p);
void SetActorPower__FP5ACTORi(void *p, int n);
struct P { char pad[0x1308]; float g; };
// name: SafeHouse port (gadget.h DrainActorPower, orig 0x1441E8)
void DrainActorPower__FP5ACTORf(struct P *p, float f)
{
    int n;
    p->g += f * g_clock.dt;
    n = (int)p->g;
    if (n) {
        int x;
        p->g -= (float)n;
        x = NActorPower__FP5ACTOR(p) - n;
        SetActorPower__FP5ACTORi(p, x > -1 ? x : 0);
    }
}
