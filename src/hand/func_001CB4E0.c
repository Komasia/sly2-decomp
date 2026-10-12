struct A { char pad[0x2D]; unsigned char b; };
struct S { char pad[0x28]; unsigned long fl; };
void func_001A6D28(struct S *p, int n);
void func_001CB4E0(struct S *p, struct A *pa)
{
    if (pa && !(p->fl & (1UL << 58))) func_001A6D28(p, pa->b);
}
