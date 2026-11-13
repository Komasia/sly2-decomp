struct S { char pad[0x194]; void *p194; void *p198; };
int FAsegaRetracted(void *p) asm("FAsegaRetracted__FP5ASEGA");
int OidSmaCur(void *p) asm("OidSmaCur__FP3SMA");
int OidSmaGoal(void *p) asm("OidSmaGoal__FP3SMA");
// name: SafeHouse port (FShipSegmentDone)
int FShipSegmentDone__FP2LO(struct S *p) { if (p->p194) return FAsegaRetracted(p->p194); { int f = 1; if (p->p198) f = OidSmaCur(p->p198) == OidSmaGoal(p->p198); return f; } }
