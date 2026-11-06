struct S { char pad[0x3C]; int n3C; };
void Init__7JOBMOVE(struct S *p);
// name: SafeHouse port (JOBUSE::Init)
void Init__6JOBUSE(struct S *p) { Init__7JOBMOVE(p); p->n3C = 0xF; }
