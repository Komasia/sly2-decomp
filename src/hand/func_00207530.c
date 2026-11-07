struct Q { char pad[0xC]; int k; int n; };
struct S { char pad[0x338]; int n; };
// name: SafeHouse port (FGuardHitMatters)
int FGuardHitMatters__FP5GUARDP5CTMSG(struct S *p, struct Q *q) { if (-q->n < p->n) return 0; switch (q->k) { case 0: case 1: case 0x80000: case 0x100000: return 0; } return 1; }
