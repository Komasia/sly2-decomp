struct S { char pad[0x30]; int n30; int pad2[2]; int n3C; };
void Init__5AIJOB(struct S *p);
// name: SafeHouse port (JOBMOVE::Init)
void Init__7JOBMOVE(struct S *p) { Init__5AIJOB(p); p->n3C = 0; p->n30 = -1; }
