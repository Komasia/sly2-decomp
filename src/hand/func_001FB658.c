struct S { char pad[0x50]; unsigned short fl; };
void func_001FB6A8(struct S *);
void func_001FB710(struct S *);
void func_001FB658(struct S *p, unsigned short m, unsigned short v)
{
    p->fl = (p->fl & ~m) | (v & m);
    if (p->fl) func_001FB6A8(p); else func_001FB710(p);
}
