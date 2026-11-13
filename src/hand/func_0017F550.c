struct S { char pad[0x194]; void *p194; void *p198; };
int FAsegaRetracted(void *p) asm("FAsegaRetracted__FP5ASEGA");
int func_001F07E8(void *p);
int func_001F07C8(void *p);
// name: SafeHouse port (FShipSegmentDone)
int FShipSegmentDone__FP2LO(struct S *p) { if (p->p194) return FAsegaRetracted(p->p194); { int f = 1; if (p->p198) f = func_001F07E8(p->p198) == func_001F07C8(p->p198); return f; } }
