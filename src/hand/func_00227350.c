struct S { char pad[0x110]; int x; };
void func_00231100(struct S *p);
void func_00227350(struct S *p)
{
    func_00231100(p);
    p->x = -1;
}
