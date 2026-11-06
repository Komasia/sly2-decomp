struct CLOCK { float t; };
extern struct CLOCK g_clock;
struct S { int a; float t; int n; };
// name: SafeHouse port (SetTargetrecTimer)
void SetTargetrecTimer__FP9TARGETRECi(struct S *p, int n) { p->t = g_clock.t; p->n = n; }
