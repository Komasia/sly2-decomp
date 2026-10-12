struct S { int a, b; int x8; int xc; int pad[2]; int x18; int x1c; };
extern char D_003D9ED0[];
void func_001AF4D8(void *p, int a, int b, int c, int d);
void func_001B0688(struct S *p)
{
    func_001AF4D8(D_003D9ED0, p->x8, p->xc, 0, p->x18);
    if (p) p->x1c |= 2;
}
