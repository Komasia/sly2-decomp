struct E { int a; int b; };
struct S { char pad[0x50]; int c; struct E *ae; };
// name: SafeHouse port (OidFromSmIsms)
int OidFromSmIsms__FP2SMi(struct S *p, int n) { if (n < 0 || n >= p->c) return -1; return p->ae[n].a; }
