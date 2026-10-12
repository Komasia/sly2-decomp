struct E { int id; int n; float t; int pad; };
struct S { char pad[0xFC]; int c; struct E a[1]; };
struct E *func_00154180(struct S *p, int id);
void func_00154080(struct S *p, struct E *pe, int n);
void func_002332B8(void *dst, void *src, int cb);
void func_00153F80(struct S *p, int id)
{
    struct E *pe = func_00154180(p, id);
    if (pe) {
        func_00154080(p, pe, 0);
        p->c--;
        func_002332B8(pe, pe + 1, (&p->a[p->c] - pe) * sizeof(struct E));
    }
}
