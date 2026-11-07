struct S { int pad[4]; int n10; int pad2[7]; int n30; };
void Init__5AIJOB(struct S *p);
void AddGuardState__FP5GUARDi(int n, int k);
// name: SafeHouse port (JOBB4::Init)
void Init__5JOBB4(struct S *p)
{
    Init__5AIJOB(p);
    AddGuardState__FP5GUARDi(p->n10, 0x22);
    p->n30 = -1;
}
