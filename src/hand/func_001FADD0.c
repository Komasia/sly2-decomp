typedef int qword __attribute__((mode(TI)));
struct S { char pad[0xE8]; int x; };
struct V { int x, y, z, w; };
qword func_001FAB48(struct S *, int, int);
void func_001FADD0(struct S *p, int a, int b, struct V *pv)
{
    if (!p->x) { pv->z = 0; pv->y = 0; pv->x = 0; }
    else *(qword *)pv = func_001FAB48(p, a, b);
}
