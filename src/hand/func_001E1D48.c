struct O { int n0; char pad[0xC]; int n10; };
struct S { char pad[0x40]; struct O *po; };
int func_001E3890(struct S *p, struct O *po);
void func_001E4EB8(struct S *p, int a, int b);
void func_001E1D48(struct S *p)
{
    if (p->po && func_001E3890(p, p->po)) {
        int f = 1;
        if (p->po->n0 == 0x1D) f = (p->po->n10 == -1);
        if (f) func_001E4EB8(p, 0, 0);
    }
}
