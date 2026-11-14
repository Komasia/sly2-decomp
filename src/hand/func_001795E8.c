typedef int qword __attribute__((mode(TI)));
#include "clock.h"
extern char g_cm[];
struct V { char pad[0x20]; qword q20; };
struct T { char pad[0x35C]; struct V *p35C; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x9C]; float gB0; float gB4; };
void Update__7JOBMOVE(struct S *p);
qword PosOfLo__FP2LO(void *p);
void JoltCm__FP2CMi(void *p, int n);
void SetAloEntryMode__FP3ALOi(struct T *t, int n);
// name: SafeHouse port (JOBHIT::Update)
void Update__6JOBHIT(struct S *p) {
    float t;
    Update__7JOBMOVE(p);
    { struct T *pt = p->pt; struct V *v = pt->p35C; v->q20 = PosOfLo__FP2LO(pt); }
    t = g_clock.t + 0.0001f;
    if (p->gB0 < t) { p->gB0 = 3.40282346638528859812e+38f; JoltCm__FP2CMi(g_cm, 0); }
    if (p->gB4 < t) { p->gB4 = 3.40282346638528859812e+38f; SetAloEntryMode__FP3ALOi(p->pt, 2); }
}
