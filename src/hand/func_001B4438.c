struct S { char pad[0x148]; unsigned long fl; };
void func_001F2108(struct S *p);
void func_001B4438(struct S *p)
{
    func_001F2108(p);
    p->fl &= ~(1UL << 35);
}
