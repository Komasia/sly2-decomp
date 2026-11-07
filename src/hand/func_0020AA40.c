struct S { char pad[0xEB8]; int a[8]; unsigned int c; };
// name: SafeHouse port (AddGuardAction)
void AddGuardAction__FP2LOi(struct S *p, int n) { if (n != -1) { if (p->c < 8) p->a[p->c++] = n; } }
