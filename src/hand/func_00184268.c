struct S { char pad[0xF0]; int f0; char p1[8]; int fc; char p2[0x84]; int x184; int p3; int x18c; int p4; int x194; int p5; int x19c; };
void func_00183F08(struct S *p);
void func_00184268(struct S *p)
{
    func_00183F08(p);
p->x184 = -1;
p->x18c = -1;
p->x194 = -1;
p->x19c = -1;
p->f0 = -1;
p->fc = 4;
}
