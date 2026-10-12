struct S { char pad[0x148]; unsigned long fl; };
void func_001F2108(struct S *p);
void func_001DE2A0(struct S *p) {
    func_001F2108(p);
    p->fl |= 0x400000000UL;
}
