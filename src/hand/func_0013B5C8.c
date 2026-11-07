struct S { char pad[0x154]; float f154; };
extern float g_clock;
// name: SafeHouse port (ExpireIn)
void ExpireIn__FP3ALOf(struct S *p, float f) { p->f154 = (p->f154 < g_clock + f) ? p->f154 : g_clock + f; }
