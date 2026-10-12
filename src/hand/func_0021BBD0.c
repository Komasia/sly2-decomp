struct S { char pad[0x15C]; int f; };
void func_001F2C30(struct S *p);
void func_0021BC08(struct S *p);
void func_0021BBD0(struct S *p)
{
    func_001F2C30(p);
    if (p->f)
        func_0021BC08(p);
}
