struct S { int pad[4]; int n10; int pad2[7]; int n30; int pad3[2]; float g3C; };
extern float D_002A5134;
void func_001EEF68(struct S *p);
void func_00209890(int n, int k);
// name: SafeHouse port (JOBB5::Init)
void Init__5JOBB5(struct S *p)
{
    func_001EEF68(p);
    func_00209890(p->n10, 0x23);
    p->n30 = -1;
    p->g3C = D_002A5134;
}
