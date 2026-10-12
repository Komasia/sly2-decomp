struct S { int n; };
extern struct S **D_003DD010;
void func_001ED470(struct S *p)
{
    int h = p->n % 0x3FFD;
    int i = h;
    struct S **pp = (struct S **)((i << 2) + (int)D_003DD010);
    goto test;
next:
    i = (i + 1) % 0x3FFD;
    pp = &D_003DD010[i];
test:
    if (*pp) goto next;
    *pp = p;
}
