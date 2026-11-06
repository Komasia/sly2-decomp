struct S { char pad[0x3C]; int n3C; };
void Init__7JOBMOVE(struct S *p);
// name: SafeHouse port (JOBSTAND::Init)
void Init__8JOBSTAND(struct S *p) { Init__7JOBMOVE(p); p->n3C = 2; }
