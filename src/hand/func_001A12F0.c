struct G { char pad[0x1030]; int x1030; };
struct S { struct G *pg; int n; };
int func_00131968(int);
void func_001A15D0(struct S *);
void func_001A12F0(struct S *p)
{
    int n;
    do {
        n = p->n;
        if (func_00131968(p->pg->x1030))
            func_001A15D0(p);
    } while (p->n != -1 && p->n != n);
}
