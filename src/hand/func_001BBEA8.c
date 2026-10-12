struct S { char pad[0xE8]; int f; };
void func_001CB518(struct S *p);
void func_001BAF18(struct S *p, int n);
void func_001F5720(struct S *p, int n);
void func_001F57C0(struct S *p, int n);
void func_001BBEA8(struct S *p)
{
    func_001CB518(p);
    func_001BAF18(p, 0x609);
    if (p->f) {
        func_001F5720(p, 1);
        func_001F57C0(p, 1);
    }
}
