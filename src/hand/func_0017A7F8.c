typedef int qword __attribute__((mode(TI)));
#include "clock.h"
extern float D_002BE6C0;
struct G { char pad[0x4020]; void *p4020; };
extern struct G g_sw;
struct R { char pad[0x54]; int n54; };
struct T { char pad[0x208]; int n208; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x1C]; int n30; int pad3; float g38; };
void Update__5AIJOB(struct S *p);
void SetState__5JOBB0i(struct S *p, int n);
qword PosOfLo__FP2LO(void *p);
struct R *func_00156698(void *p, qword q, struct T *t);
// name: SafeHouse port (JOBB0::Update)
void Update__5JOBB0(struct S *p) {
    int s;
    Update__5AIJOB(p);
    do {
        s = p->n30;
        if (s < 4) { if (s >= 2 && p->pt->n208) SetState__5JOBB0i(p, -1); }
    } while (s != p->n30);
    if (s == 1 || s == 4) {
        if (g_clock.t - p->g38 > D_002BE6C0) {
            struct G *g = &g_sw;
            p->g38 = g_clock.t;
            func_00156698(g->p4020, PosOfLo__FP2LO(p->pt), p->pt)->n54 = 3;
        }
    }
}
