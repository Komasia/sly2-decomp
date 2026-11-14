#include "clock.h"
struct P { char pad[0x30]; int state; float tState; };
void UnlockJob__FP5AIJOB(struct P *p);
void LockJob__FP5AIJOB(struct P *p);
// name: SafeHouse port (JOBSLYATTACK::SetState)
void SetState__12JOBSLYATTACKi(struct P *p, int state)
{
    if (state == p->state) return;
    switch (p->state) {
    case 2: case 3: case 4:
        UnlockJob__FP5AIJOB(p);
    }
    p->state = state;
    p->tState = g_clock.t;
    switch (state) {
    case 2: case 3: case 4:
        LockJob__FP5AIJOB(p);
    }
}
