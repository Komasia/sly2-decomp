struct S { int pad[4]; int n10; int pad2[7]; int n30; int pad3[2]; float g3C; };
extern float D_002A5134;
void Init__5AIJOB(struct S *p);
void AddGuardState__FP5GUARDi(int n, int k);
// name: SafeHouse port (JOBB5::Init)
void Init__5JOBB5(struct S *p)
{
    Init__5AIJOB(p);
    AddGuardState__FP5GUARDi(p->n10, 0x23);
    p->n30 = -1;
    p->g3C = D_002A5134;
}
