struct E { int id; int n; float t; int pad; };
struct S { char pad[0xFC]; int c; struct E a[1]; };
int func_001541D8(struct S *p, int id, int n);
void func_00154080(struct S *p, struct E *pe, int n);
void func_00153DE0(struct S *p)
{
    int i;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->a[i];
        func_00154080(p, pe, func_001541D8(p, pe->id, pe->n));
    }
}
